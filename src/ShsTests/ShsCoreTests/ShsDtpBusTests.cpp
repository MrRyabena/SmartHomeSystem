#include <chrono>
#include <thread>

#include <gtest/gtest.h>

#include <shs_API.h>
#include <shs_DTP_API.h>
#include <shs_DTPbus.h>
#include <shs_DTPbusReceiveContext.h>
#include <shs_DTPbusStatus.h>
#include <shs_ByteCollector.h>
#include <shs_Random.h>

/**
 * @brief Test bus that simulates a bus with a ByteCollector buffer.
 */
class TestBus
{
public:
    explicit TestBus(shs::ByteCollector<> buf) : m_buf(std::move(buf)) {}

    size_t available() const { return m_buf.readAvailable(); }
    uint8_t read() { uint8_t value; m_buf.get(value); return value; }
    uint8_t write([[maybe_unused]] const uint8_t* data, const size_t size) { m_output.write(data, size); return size; }

    shs::ByteCollectorReadIterator<> getOutput() { return m_output.getReadIt(); }
    auto getOutputBegin() { return m_output.begin(); }
    auto getOutputEnd() { return m_output.end(); }

    shs::ByteCollector<> m_output;
protected:
    shs::ByteCollector<> m_buf;
};

/**
 * @brief Test handler that collects data from the bus.
 */
class TestHandler : public shs::API
{
public:
    explicit TestHandler() : shs::API(0) {}
    shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override
    {
        for (auto i = 0; i < it.size(); ++i) data.push_back(it[i], 1);
        return {};
    }

    shs::ByteCollector<> data;
};

/**
 * @brief Test fixture for DtpBus tests.
 */
class DtpBusTests : public testing::Test
{
protected:
    shs::ByteCollector<> message_buf;

    shs::DTPbusReceiveContext context;

    DtpBusTests()
    {
        context.receive_timer.setTimeout(10);
    }
};

/**
 * @brief Test fixture for DtpBus random tests.
 */
class DtpBusRandomTest : public testing::TestWithParam<shs::ByteCollector<>>
{
protected:
    shs::DTPbusReceiveContext context;

    DtpBusRandomTest()
    {
        context.receive_timer.setTimeout(10);
    }

public:
    static std::vector<shs::ByteCollector<>> GenerateRandomInputs()
    {
        std::vector<shs::ByteCollector<>> inputs;
        shs::Random<uint8_t> random(0, 255);
        random.autoSeed();

        for (int i = 0; i < 500; i++)
        {
            auto size = random.get();        // Random size between 0 and 255
            shs::ByteCollector<> buf(size);
            buf.push_back(size, 1);          // First byte is the size
            if (size > 1)
            {
                for (size_t i = 0; i < size - 1; ++i)
                {
                    buf.push_back(random.get(), 1);
                }
            }
            inputs.push_back(std::move(buf));
        }
        return inputs;
    }

};

TEST_F(DtpBusTests, processBusEmptyInputTest)
{
    message_buf.reserve(10);
    TestBus testBus(std::move(message_buf));

    auto status = shs::DTPbus::processBus(testBus, context);
    EXPECT_EQ(status, shs::DTPbus::Status::no_data);
    EXPECT_EQ(context.receive_length, 0);
    EXPECT_EQ(testBus.available(), 0);

}

TEST_F(DtpBusTests, processBusResetTimerTest)
{
    message_buf.reserve(10);

    for (uint8_t i = 0; i < 10; ++i) message_buf.push_back(100, 1);

    {
        TestBus testBus(std::move(message_buf));

        auto status = shs::DTPbus::processBus(testBus, context);
        EXPECT_EQ(status, shs::DTPbus::Status::packet_is_expected);
        EXPECT_EQ(context.receive_length, 100);
        EXPECT_EQ(testBus.available(), 9);

        std::this_thread::sleep_for(std::chrono::milliseconds(15));
        status = shs::DTPbus::processBus(testBus, context);
        EXPECT_EQ(status, shs::DTPbus::Status::receive_timeout_error);
    }

    message_buf.clear();
    for (auto i = 0; i < 10; i++) message_buf.push_back(10, 1);
    TestBus testBus(std::move(message_buf));
    auto status = shs::DTPbus::processBus(testBus, context);
    EXPECT_EQ(status, shs::DTPbus::Status::packet_received);
}

TEST_F(DtpBusTests, checkBusProcessPacketTest)
{
    message_buf.reserve(10);
    for (uint8_t i = 0; i < 10; ++i) message_buf.push_back(10, 1);
    TestBus testBus(message_buf);
    TestHandler testHandler;

    context.handler = &testHandler;

    auto status = shs::DTPbus::checkBus(testBus, context);
    EXPECT_EQ(status, shs::DTPbus::Status::packet_processed);


    bool elements_are_equal = std::equal(
        testHandler.data.begin(), testHandler.data.end(),
        message_buf.begin()
    );

    EXPECT_TRUE(elements_are_equal);
}

/**
 * @brief Instantiate the DtpBusRandomTest test suite.
 */
INSTANTIATE_TEST_SUITE_P(DtpBusRandomTest,
    DtpBusRandomTest,
    testing::ValuesIn(DtpBusRandomTest::GenerateRandomInputs()));

TEST_P(DtpBusRandomTest, processBusRandomTest)
{
    auto input = GetParam();
    using Status = shs::DTPbus::Status;
    auto result = input.size() == 1 && input[0] < 2 ? Status::invalid_recipient : Status::packet_received;
    TestBus testBus(std::move(input));

    auto status = shs::DTPbus::processBus(testBus, context);
    EXPECT_EQ(status, result);
}

TEST_F(DtpBusTests, handleDtpApiInitialPacketTest)
{
    auto packet = shs::DTP_API::getInitialPacket();
    auto answer_packet = shs::DTP_API::getInitialAnswerPacket(0, true);
    TestBus testBus(std::move(packet.bc));

    auto status = shs::DTPbus::checkBus(testBus, context);
    EXPECT_EQ(status, shs::DTPbus::Status::packet_received);

    bool elements_are_equal = std::equal(
        testBus.getOutputBegin(), testBus.getOutputEnd(),
        answer_packet.bc.begin()
    );

    EXPECT_TRUE(elements_are_equal);
}

TEST_F(DtpBusTests, handleDtpApiConnectionRequestPacketTest)
{
    auto packet = shs::DTP_API::getConnectionRequestPacket();
    auto answer_packet = shs::DTP_API::getConnectionRequestAnswerPacket(0, true);
    TestBus testBus(std::move(packet.bc));

    auto status = shs::DTPbus::checkBus(testBus, context);
    EXPECT_EQ(status, shs::DTPbus::Status::packet_received);

    bool elements_are_equal = std::equal(
        testBus.getOutputBegin(), testBus.getOutputEnd(),
        answer_packet.bc.begin()
    );
    EXPECT_TRUE(elements_are_equal);
}
