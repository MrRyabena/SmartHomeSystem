
cmake_minimum_required(VERSION 3.27)

project(SHScore VERSION 2.4.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(SOURCES
    shs_Load
    shs_Sensor
    shs_DTP

    shs_API.h
    shs_APIids.h
    shs_APIprint.h
    shs_ByteCollector.h
    shs_ByteCollectorIterator.h
    shs_CRC.cpp
    shs_CRC.h
    shs_Config.h
    shs_ControlWiFi.h
    shs_CreateProcess.h
    shs_DTP.cpp
    shs_DTP.h
    shs_DTP_API.cpp
    shs_DTP_API.h
    shs_DTPbus.h
    shs_DTPbusController.h
    shs_DTPbusController.cpp
    shs_DTPbusPolicy.h
    shs_DTPbusReceiveContext.h
    shs_DTPbusReceiveContext.cpp
    shs_DTPbusStatus.h
    shs_DTPdiscover.cpp
    shs_DTPdiscover.h
    shs_DTPless.h
    shs_DTPpacket.cpp
    shs_DTPpacket.h
    shs_DTPstreamBus.h
    shs_EventTracker.h
    shs_ID.h
    shs_IP.h
    shs_Load.h
    shs_LoadSwitch.h
    shs_LoadVirtual.cpp
    shs_LoadVirtual.h
    shs_Load_API.h
    shs_MutexSafe.h
    shs_Process.h
    shs_ProcessesHandler.h
    shs_ProgramTime.h
    shs_Sensor.h
    shs_SensorAnalog.h
    shs_SensorVirtual.cpp
    shs_SensorVirtual.h
    shs_Sensor_API.cpp
    shs_Sensor_API.h
    shs_SimpleFixed.h
    shs_SortedBuf.h
    shs_Stream.h
    shs_Time.h
    shs_Timer.h
    shs_algorithm.h
    shs_debug.h
    shs_settings_private.h
    shs_types.h
    shs_version.h
)

if(SHS_CMF_UNUSE_SHS_SETTINGS)
    set(SHS_SF_UNUSE_SHS_SETTINGS ON)
else()
    list(APPEND SOURCES shs_settings.h)
endif()

set(NETWORK_SOURCES
    shs_Network
    shs_TcpServer.cpp
    shs_TcpServer.h
    shs_TcpSocket.cpp
    shs_TcpSocket.h

    shs_UDP.cpp
    shs_UDP.h
    shs_UDPbus.h
)

set(QT_SOURCES
    shs_qt_TcpSocket.cpp
    shs_qt_TcpSocket.h
    shs_qt_Udp.cpp
    shs_qt_Udp.h
)


if(SHS_CMF_QT)
    message(STATUS "using Qt")
    find_package(Qt6 REQUIRED COMPONENTS Core Network Quick)
    list(APPEND SOURCES ${NETWORK_SOURCES})
    list(APPEND SOURCES ${QT_SOURCES})
else()
    message(STATUS "no qt")
endif()

add_library(SHScore ${SOURCES})

target_include_directories(SHScore
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

if(SHS_CMF_UNUSE_SHS_SETTINGS)
    target_compile_definitions(SHScore PRIVATE SHS_SF_UNUSE_SHS_SETTINGS)
endif()

if(SHS_CMF_QT)
    target_link_libraries(SHScore PRIVATE Qt6::Core Qt6::Quick)
    target_link_libraries(SHScore PRIVATE Qt6::Core Qt6::Network)
endif()

target_compile_features(SHScore PRIVATE cxx_std_14)
