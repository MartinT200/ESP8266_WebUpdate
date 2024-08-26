
void update_started() {
  Serial.println("CALLBACK:  HTTP update process started");
}

void update_finished() {
  Serial.println("CALLBACK:  HTTP update process finished");
  delay(2000);
  Serial.println("reboot?");
  delay(2000);
  Serial.println("reboot??");
  delay(2000);
  Serial.println("reboot??? :-)"); 
}

void update_progress(int cur, int total) {
  Serial.printf("CALLBACK:  HTTP update process at %d of %d bytes...\n", cur, total);
}

void update_error(int err) {
  Serial.printf("CALLBACK:  HTTP update fatal error code %d\n", err);
}

void otaSetup(){
    ESPhttpUpdate.setClientTimeout(2000);  // default was 8000
    // Add optional callback notifiers
    ESPhttpUpdate.onStart(update_started);
    ESPhttpUpdate.onEnd(update_finished);
    ESPhttpUpdate.onProgress(update_progress);
    ESPhttpUpdate.onError(update_error);
    ESPhttpUpdate.setLedPin(LED_BUILTIN, LOW);
}



void ota(String url){
  t_httpUpdate_return ret = ESPhttpUpdate.update(client, url);
  // Or:
  // t_httpUpdate_return ret = ESPhttpUpdate.update(client, "server", 80, "file.bin");
  switch (ret) {
  case HTTP_UPDATE_FAILED: Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str()); break;

  case HTTP_UPDATE_NO_UPDATES: Serial.println("HTTP_UPDATE_NO_UPDATES"); break;

  case HTTP_UPDATE_OK: Serial.println("HTTP_UPDATE_OK"); break;
  }
}