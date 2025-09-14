#ifndef XRTCSDK_XRTC_RTC_PC_NETWORK_CONTROLLER_H_
#define XRTCSDK_XRTC_RTC_PC_NETWORK_CONTROLLER_H_
#include<api/transport/network_types.h>
namespace xrtc {

class NetworkControllerInterface {
    public:
        virtual ~NetworkControllerInterface() {}
        virtual webrtc::NetworkControlUpdate OnNetworkOk(const webrtc::TargetRateConstraints &constraints) = 0;
        virtual webrtc::NetworkControlUpdate OnTransportpacketsFeedback(
            const webrtc::TransportpacketsFeedback& ) = 0;
        virtual webrtc::NetworkControlUpdate OnRttUpdate(int64_t rtt_ms) = 0;
        virtual webrtc::NetworkControlUpdate OnTransportLoss(int32_t packets_lost,
            int32_t num_of_packets,webrtc::Timestamp at_time) = 0;
};
} // namespace xrtc

#endif // XRTCSDK_XRTC_RTC_PC_NETWORK_CONTROLLER_H_
