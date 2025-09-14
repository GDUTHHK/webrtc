#include "xrtc/rtc/modules/congestion_controller/google_gcc/acknowledged_bitrate_estimator.h"

namespace xrtc {
AcknowledgedBitrateEstimator::AcknowledgedBitrateEstimator():
    bitrate_estimator_(std::make_unique<BitrateEstimator>()) {
}
AcknowledgedBitrateEstimator::~AcknowledgedBitrateEstimator() {
}
void AcknowledgedBitrateEstimator::IncomingPacketFeedbackVector(const webrtc::PacketResult& packet_feedback_vector) {
    for(const auto& packet : packet_feedback_vector) {
        webrtc::DataSize acknowledged_estimate = packet.send_packet.size;
        bitrate_estimator_->Update(packet.receive_time,acknowledged_estimate);
    }
}

absl::optional<webrtc::DataRate> AcknowledgedBitrateEstimator::bitrate() const {
    return bitrate_estimator_->bitrate();
}
} // namespace xrtc