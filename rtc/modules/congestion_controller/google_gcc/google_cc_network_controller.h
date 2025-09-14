#ifndef XRTCSDK_XRTC_RTC_MODULES_CONGESTION_CONTROLLER_GOOGLE_GCC_GOOGLE_CC_NETWORK_CONTROLLER_H_
#define XRTCSDK_XRTC_RTC_MODULES_CONGESTION_CONTROLLER_GOOGLE_GCC_GOOGLE_CC_NETWORK_CONTROLLER_H_

#include "xrtc/rtc/modules/congestion_controller/google_gcc/delay_based_bwe.h"
#include "xrtc/rtc/pc/network_controller.h"
#include "xrtc/rtc/modules/congestion_controller/google_gcc/acknowledged_bitrate_estimator.h"
#include "xrtc/rtc/modules/congestion_controller/google_gcc/send_side_bandwidth_estimator.h"
namespace xrtc {

    //作为带宽估计或者拥塞控制的模块
class GoogleCCNetworkController : public NetworkControllerInterface {
public:
    GoogleCCNetworkController();
    ~GoogleCCNetworkController() override;
    webrtc::NetworkControlUpdate OnNetworkOk(const webrtc::TargetRateConstraints &constraints) override;
    webrtc::NetworkControlUpdate OnTransportpacketsFeedback(
        const webrtc::TransportpacketsFeedback& report) override;
    webrtc::NetworkControlUpdate OnRttUpdate(int64_t rtt_ms) override;
    webrtc::NetworkControlUpdate OnTransportLoss(int32_t packets_lost,
        int32_t num_of_packets,webrtc::Timestamp at_time) override;
private:
    std::unique_ptr<DelayBasedBwe> delay_based_bwe_;
    std::unique_ptr<AcknowledgedBitrateEstimator> acknowledged_bitrate_estimator_;
    std::unique_ptr<SendSideBandwidthEstimator> bandwidth_estimator_;
};
} // namespace xrtc
#endif // XRTCSDK_XRTC_RTC_MODULES_CONGESTION_CONTROLLER_GOOGLE_GCC_GOOGLE_CC_NETWORK_CONTROLLER_H_