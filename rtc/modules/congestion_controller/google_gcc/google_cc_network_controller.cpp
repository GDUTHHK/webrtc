#include "xrtc/rtc/modules/congestion_controller/google_gcc/google_cc_network_controller.h"

namespace xrtc {
GoogleCCNetworkController::GoogleCCNetworkController():
    delay_based_bwe_(std::make_unique<DelayBasedBwe>()),
    acknowledged_bitrate_estimator_(std::make_unique<AcknowledgedBitrateEstimator>()),
    bandwidth_estimator_(std::make_unique<SendSideBandwidthEstimator>()) {

}
GoogleCCNetworkController::~GoogleCCNetworkController() {
}
webrtc::NetworkControlUpdate GoogleCCNetworkController::OnTransportpacketsFeedback(
    const webrtc::TransportpacketsFeedback& report) {
    if(report.packet_feedbacks.empty()) {
        return webrtc::NetworkControlUpdate();
    }
    //将数据包反馈信息传递给吞吐量估计器
    //里面只包含对面确认接收到的数据包
    acknowledged_bitrate_estimator_->IncomingPacketFeedbackVector(report.SortedByReceiveTime());

    absl::optional<webrtc::DataRate> acked_bitrate = acknowledged_bitrate_estimator_->bitrate();
    DelayBasedBwe::Result result;
    result = delay_based_bwe_->IncomingPacketFeedbackVector(report,acked_bitrate);
    return webrtc::NetworkControlUpdate();
}


webrtc::NetworkControlUpdate GoogleCCNetworkController::OnRttUpdate(int64_t rtt_ms) {
    bandwidth_estimator_->UpdateRtt(webrtc::TimeDelta::Millis(rtt_ms));
    delay_based_bwe_->OnRttUpdate(rtt_ms);
    return webrtc::NetworkControlUpdate();
}

webrtc::NetworkControlUpdate GoogleCCNetworkController::OnNetworkOk(const webrtc::TargetRateConstraints &constraints)
{
    bandwidth_estimator_->SetBitrates(constraints.start_bitrate,
        constraints.min_data_rate.value_or(webrtc::DataRate::Zero()),
        constraints.max_data_rate.value_or(webrtc::DataRate::PlusInfinity()));
    return webrtc::NetworkControlUpdate();
}

webrtc::NetworkControlUpdate GoogleCCNetworkController::OnTransportLoss(int32_t packets_lost,
    int32_t num_of_packets,webrtc::Timestamp at_time) {
    bandwidth_estimator_->UpdatePacketsLost(packets_lost,num_of_packets,at_time);
    return webrtc::NetworkControlUpdate();
}
}