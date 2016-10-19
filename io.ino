
void set_outputs() {
  digitalWrite(out_spare, spare_disabled);
  digitalWrite(out_feed, feeder_disabled);
  digitalWrite(out_str, straightener_disabled);
  digitalWrite(out_brake, brake_disabled);
  digitalWrite(out_cut, cutter_enabled );
  digitalWrite(out_eject, ejector_enabled);
}

void reset_outputs() {
  feeder_disabled = true;
  straightener_disabled = true;
  brake_disabled = true;
  spare_disabled = true;
  cutter_enabled = false;
  ejector_enabled = false;
}
