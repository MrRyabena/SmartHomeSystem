#include <chrono>
#include <thread>

#include <gtest/gtest.h>

#include <shs_API.h>
#include <shs_DTP_API.h>
#include <shs_DTPbus.h>
#include <shs_DTPbusReceiveContext.h>
#include <shs_DTPbusReceiveStatus.h>
#include <shs_DTPbusPolicy.h>
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

class DtpTestBus : public shs::DTPbus
{
public:
    explicit DtpTestBus(TestBus bus)
        : DTPbus(0, shs::DTPbusPolicy::STATIC_BUS),
        m_bus(std::move(bus))
    {
        m_context.receive_timer.setTimeout(10);
    }

    bool isActive() const override { return true; }
    void setActive([[maybe_unused]] const bool active) override {}

    ReceiveStatus checkBus() override { return shs::DTPbus::checkBus(m_bus); }

    void start() override {}
    void tick() override {}
    void stop() override {}

    uint8_t sendPacket(const shs::DTPpacket& packet) override { return shs::DTPbus::sendPacket(m_bus, packet); }
    uint8_t sendRAW(shs::ByteCollector<>& bc) override { return shs::DTPbus::sendRAW(m_bus, bc); }
    uint8_t sendRAW(shs::ByteCollectorReadIterator<>& it) override { return shs::DTPbus::sendRAW(m_bus, it); }
    uint8_t sendRAW(const uint8_t* data, const uint8_t size) override { return shs::DTPbus::sendRAW(m_bus, data, size); }

    TestBus m_bus;
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
    TestBus test_bus(std::move(message_buf));

    auto status = shs::DTPbus::processBus(test_bus, context);
    EXPECT_EQ(status, shs::DTPbus::ReceiveStatus::no_data);
    EXPECT_EQ(context.status, status);
    EXPECT_EQ(context.receive_length, 0);
    EXPECT_EQ(test_bus.available(), 0);

}

TEST_F(DtpBusTests, busEmptyInputTest)
{
    TestBus test_bus{ shs::ByteCollector<>{} };
    DtpTestBus dtp_bus(std::move(test_bus));

    auto status = dtp_bus.checkBus();
    EXPECT_EQ(status, shs::DTPbus::ReceiveStatus::no_data);
    EXPECT_EQ(dtp_bus.getReceiveStatus(), status);
    EXPECT_EQ(dtp_bus.getLastData().size(), 0);
}

TEST_F(DtpBusTests, processBusResetTimerTest)
{
    message_buf.reserve(10);

    for (uint8_t i = 0; i < 10; ++i) message_buf.push_back(100, 1);

    {
        TestBus test_bus(std::move(message_buf));

        auto status = shs::DTPbus::processBus(test_bus, context);
        EXPECT_EQ(status, shs::DTPbus::ReceiveStatus::packet_is_expected);
        EXPECT_EQ(context.status, status);
        EXPECT_EQ(context.receive_length, 100);
        EXPECT_EQ(test_bus.available(), 9);

        std::this_thread::sleep_for(std::chrono::milliseconds(15));
        status = shs::DTPbus::processBus(test_bus, context);
        EXPECT_EQ(status, shs::DTPbus::ReceiveStatus::receive_timeout_error);
        EXPECT_EQ(context.status, status);
    }

    message_buf.clear();
    for (auto i = 0; i < 10; i++) message_buf.push_back(10, 1);
    TestBus test_bus(std::move(message_buf));
    auto status = shs::DTPbus::processBus(test_bus, context);
    EXPECT_EQ(status, shs::DTPbus::ReceiveStatus::packet_received);
    EXPECT_EQ(context.status, status);
}

TEST_F(DtpBusTests, busResetTimerTest)
{
    message_buf.reserve(10);
    for (uint8_t i = 0; i < 10; ++i) message_buf.push_back(100, 1);

    TestBus test_bus(std::move(message_buf));
    {
        DtpTestBus dtp_bus(std::move(test_bus));

        auto status = dtp_bus.checkBus();
        EXPECT_EQ(status, shs::DTPbus::ReceiveStatus::packet_is_expected);
        EXPECT_EQ(dtp_bus.getReceiveStatus(), status);
        EXPECT_EQ(dtp_bus.getLastData().size(), 0);

        std::this_thread::sleep_for(std::chrono::milliseconds(15));
        status = dtp_bus.checkBus();
        EXPECT_EQ(status, shs::DTPbus::ReceiveStatus::receive_timeout_error);
        EXPECT_EQ(dtp_bus.getReceiveStatus(), status);
        EXPECT_EQ(dtp_bus.getLastData().size(), 0);
    }

    message_buf.clear();
    for (auto i = 0; i < 10; i++) message_buf.push_back(10, 1);
    {
        TestBus testBus2(std::move(message_buf));
        DtpTestBus dtp_bus(std::move(testBus2));

        auto status = dtp_bus.checkBus();
        EXPECT_EQ(status, shs::DTPbus::ReceiveStatus::packet_received);
        EXPECT_EQ(dtp_bus.getReceiveStatus(), status);
    }
}

TEST_F(DtpBusTests, checkBusProcessPacketTest)
{
    message_buf.reserve(10);
    for (uint8_t i = 0; i < 10; ++i) message_buf.push_back(10, 1);
    TestBus test_bus(message_buf);
    TestHandler testHandler;

    context.handler = &testHandler;

    auto status = shs::DTPbus::checkBus(test_bus, context);
    EXPECT_EQ(status, shs::DTPbus::ReceiveStatus::packet_processed);
    EXPECT_EQ(context.status, status);

    bool elements_are_equal = std::equal(
        testHandler.data.begin(), testHandler.data.end(),
        message_buf.begin()
    );

    EXPECT_TRUE(elements_are_equal);
}

TEST_F(DtpBusTests, busProcessPacketTest)
{
    message_buf.reserve(10);
    for (uint8_t i = 0; i < 10; ++i) message_buf.push_back(10, 1);
    TestBus test_bus(message_buf);
    TestHandler testHandler;

    DtpTestBus dtp_bus(std::move(test_bus));
    dtp_bus.setHandler(&testHandler);

    auto status = dtp_bus.checkBus();
    EXPECT_EQ(status, shs::DTPbus::ReceiveStatus::packet_processed);
    EXPECT_EQ(dtp_bus.getReceiveStatus(), status);

    bool elements_are_equal = std::equal(
        testHandler.data.begin(), testHandler.data.end(),
        message_buf.begin()
    );

    EXPECT_TRUE(elements_are_equal);
}

/**
 * @brief Instantiate the DtpBusRandomTest test suite.
 */
INSTANTIATE_TEST_SUITE_P(
    DtpBusRandomInputs,
    DtpBusRandomTest,
    testing::ValuesIn(DtpBusRandomTest::GenerateRandomInputs()));

TEST_P(DtpBusRandomTest, processBusRandomTest)
{
    auto input = GetParam();
    using Status = shs::DTPbus::ReceiveStatus;
    auto result = input.size() == 1 && input[0] < 2 ? Status::invalid_recipient : Status::packet_received;
    TestBus test_bus(std::move(input));

    auto status = shs::DTPbus::processBus(test_bus, context);
    EXPECT_EQ(status, result);
    EXPECT_EQ(context.status, status);
}

TEST_P(DtpBusRandomTest, busRandomTest)
{
    auto input = GetParam();
    using Status = shs::DTPbus::ReceiveStatus;
    auto result = input.size() == 1 && input[0] < 2 ? Status::invalid_recipient : Status::packet_received;
    TestBus test_bus(std::move(input));
    DtpTestBus dtp_bus(std::move(test_bus));

    auto status = dtp_bus.checkBus();
    EXPECT_EQ(status, result);
    EXPECT_EQ(dtp_bus.getReceiveStatus(), status);
}

TEST_F(DtpBusTests, handleDtpApiInitialPacketTest)
{
    auto packet = shs::DTP_API::getInitialPacket();
    auto answer_packet = shs::DTP_API::getInitialAnswerPacket(0, true);
    TestBus test_bus(std::move(packet.bc));

    auto status = shs::DTPbus::checkBus(test_bus, context);
    EXPECT_EQ(status, shs::DTPbus::ReceiveStatus::packet_received);
    EXPECT_EQ(context.status, status);

    bool elements_are_equal = std::equal(
        test_bus.getOutputBegin(), test_bus.getOutputEnd(),
        answer_packet.bc.begin()
    );

    EXPECT_TRUE(elements_are_equal);
}

TEST_F(DtpBusTests, busHandleDtpApiInitialPacketTest)
{
    auto packet = shs::DTP_API::getInitialPacket();
    auto answer_packet = shs::DTP_API::getInitialAnswerPacket(0, true);
    TestBus test_bus(std::move(packet.bc));
    DtpTestBus dtp_bus(std::move(test_bus));

    auto status = dtp_bus.checkBus();
    EXPECT_EQ(status, shs::DTPbus::ReceiveStatus::packet_received);
    EXPECT_EQ(dtp_bus.getReceiveStatus(), status);
    EXPECT_EQ(dtp_bus.getLastData().size(), answer_packet.bc.size());

    bool elements_are_equal = std::equal(
        answer_packet.bc.begin(), answer_packet.bc.end(),
        dtp_bus.m_bus.getOutputBegin()
    );

    EXPECT_TRUE(elements_are_equal);
}

TEST_F(DtpBusTests, handleDtpApiConnectionRequestPacketTest)
{
    auto packet = shs::DTP_API::getConnectionRequestPacket();
    auto answer_packet = shs::DTP_API::getConnectionRequestAnswerPacket(0, true);
    TestBus test_bus(std::move(packet.bc));

    auto status = shs::DTPbus::checkBus(test_bus, context);
    EXPECT_EQ(status, shs::DTPbus::ReceiveStatus::packet_received);
    EXPECT_EQ(context.status, status);

    bool elements_are_equal = std::equal(
        test_bus.getOutputBegin(), test_bus.getOutputEnd(),
        answer_packet.bc.begin()
    );
    EXPECT_TRUE(elements_are_equal);
}

TEST_F(DtpBusTests, busHandleDtpApiConnectionRequestPacketTest)
{
    auto packet = shs::DTP_API::getConnectionRequestPacket();
    auto answer_packet = shs::DTP_API::getConnectionRequestAnswerPacket(0, true);
    TestBus test_bus(std::move(packet.bc));
    DtpTestBus dtp_bus(std::move(test_bus));

    auto status = dtp_bus.checkBus();
    EXPECT_EQ(status, shs::DTPbus::ReceiveStatus::packet_received);
    EXPECT_EQ(dtp_bus.getReceiveStatus(), status);

    bool elements_are_equal = std::equal(
        answer_packet.bc.begin(), answer_packet.bc.end(),
        dtp_bus.m_bus.getOutputBegin()
    );
    EXPECT_TRUE(elements_are_equal);
}
