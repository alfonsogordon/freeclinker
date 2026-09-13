#pragma once

#include <Preferences.h>
#include <Stream.h>
#include <stdint.h>

class CameraRegistry;
class Camera;
struct CameraData;

class ConfigManager {
public:
    static constexpr uint8_t OSD_TPL_LEN = 32;

    struct Config {
        uint32_t disarmStopDelayMs; bool stopOnDisarm; uint8_t auxChannel; uint8_t auxMode; uint8_t cameraType; uint8_t cameraMatchMode; bool cameraWakeGuard; bool debugBle; bool lowPowerMode; uint32_t wifiApStartDelaySec; bool wifiApEnabled;
        char osd1Tpl[OSD_TPL_LEN]; char osd2Tpl[OSD_TPL_LEN]; char osd3Tpl[OSD_TPL_LEN]; char osd4Tpl[OSD_TPL_LEN]; bool bf45Compat; bool pilotNameEnabled; char pilotNameTpl[OSD_TPL_LEN]; bool craftNameEnabled; char craftNameTpl[OSD_TPL_LEN];
        bool fpvStateMode; bool fpvErrorEnabled; char fpvErrorText[OSD_TPL_LEN]; bool fpvReadyEnabled; char fpvReadyText[OSD_TPL_LEN]; bool fpvRecordingEnabled; char fpvRecordingText[OSD_TPL_LEN]; bool fpvRecFlash;
        bool fpvLowBatteryEnabled; uint8_t fpvLowBatteryPct; bool fpvLowBatteryReadyFlash; bool fpvLowBatteryRecText; char fpvLowBatteryText[OSD_TPL_LEN]; bool fpvLowRecTimeEnabled; uint16_t fpvLowRecTimeMin; bool fpvLowRecReadyWarning; bool fpvLowRecRecordingWarning; char fpvLowRecTimeText[OSD_TPL_LEN]; bool fpvHotWarningEnabled; bool fpvHotReadyWarning; bool fpvHotRecordingWarning; char fpvHotWarningText[OSD_TPL_LEN]; bool fpvPreArmReminderEnabled; char fpvPreArmReminderText[OSD_TPL_LEN]; uint16_t fpvPreArmReminderShowMs; uint16_t fpvPreArmReminderIntervalMs;
    };

    static constexpr uint32_t DEFAULT_DISARM_STOP_DELAY_MS = 5000;
    static constexpr bool DEFAULT_STOP_ON_DISARM = true;
    static constexpr uint8_t DEFAULT_AUX_CHANNEL = 0;
    static constexpr uint8_t DEFAULT_AUX_MODE = 0x00;
    static constexpr uint8_t DEFAULT_CAMERA_TYPE = 1;
    static constexpr uint8_t DEFAULT_CAMERA_MATCH_MODE = 0;
    static constexpr bool DEFAULT_CAMERA_WAKE_GUARD = true;
    static constexpr bool DEFAULT_DEBUG_BLE = false;
    static constexpr bool DEFAULT_LOW_POWER_MODE = true;
    static constexpr uint32_t DEFAULT_WIFI_AP_START_DELAY_SEC = 30;
    static constexpr bool DEFAULT_WIFI_AP_ENABLED = false;
    static constexpr const char *DEFAULT_OSD1_TPL = "{batt}";
    static constexpr const char *DEFAULT_OSD2_TPL = "{state} {recdur}";
    static constexpr const char *DEFAULT_OSD3_TPL = "{mode} {res} {fps} {eis}";
    static constexpr const char *DEFAULT_OSD4_TPL = "{rectf} {rcap}";
    static constexpr bool DEFAULT_BF45_COMPAT = false;
    static constexpr bool DEFAULT_PILOT_NAME_ENABLED = true;
    static constexpr const char *DEFAULT_PILOT_NAME_TPL = "{stateonly} {batt} {rectf}";
    static constexpr bool DEFAULT_CRAFT_NAME_ENABLED = false;
    static constexpr const char *DEFAULT_CRAFT_NAME_TPL = "{res} {fps}";
    static constexpr bool DEFAULT_FPV_STATE_MODE = true;
    static constexpr bool DEFAULT_FPV_ERROR_ENABLED = true;
    static constexpr const char *DEFAULT_FPV_ERROR_TEXT = "{state}";
    static constexpr bool DEFAULT_FPV_READY_ENABLED = true;
    static constexpr const char *DEFAULT_FPV_READY_TEXT = "{state}";
    static constexpr bool DEFAULT_FPV_RECORDING_ENABLED = true;
    // @ARM is configurator metadata for the signed-off REC-only takeover.
    static constexpr const char *DEFAULT_FPV_RECORDING_TEXT = "@ARM:{state}";
    static constexpr bool DEFAULT_FPV_REC_FLASH = true;
    static constexpr bool DEFAULT_FPV_LOW_BATTERY_ENABLED = true;
    static constexpr uint8_t DEFAULT_FPV_LOW_BATTERY_PCT = 10;
    static constexpr bool DEFAULT_FPV_LOW_BAT_READY_FLASH = true;
    static constexpr bool DEFAULT_FPV_LOW_BAT_REC_TEXT = true;
    static constexpr const char *DEFAULT_FPV_LOW_BATTERY_TEXT = "@1:BATT LOW";
    static constexpr bool DEFAULT_FPV_LOW_REC_ENABLED = true;
    static constexpr uint16_t DEFAULT_FPV_LOW_REC_MIN = 5;
    static constexpr bool DEFAULT_FPV_LOW_REC_READY = true;
    static constexpr bool DEFAULT_FPV_LOW_REC_RECORDING = true;
    static constexpr const char *DEFAULT_FPV_LOW_REC_TEXT = "REC LOW";
    static constexpr bool DEFAULT_FPV_HOT_ENABLED = true;
    static constexpr bool DEFAULT_FPV_HOT_READY = true;
    static constexpr bool DEFAULT_FPV_HOT_RECORDING = true;
    static constexpr const char *DEFAULT_FPV_HOT_TEXT = "CAM HOT";
    static constexpr bool DEFAULT_FPV_PREARM_ENABLED = true;
    // Temporary CLEAN LENS is ON by default and targets Custom Message 2.
    static constexpr const char *DEFAULT_FPV_PREARM_TEXT = "@2:CLEAN LENS";
    static constexpr uint16_t DEFAULT_FPV_PREARM_SHOW_MS = 1000;
    static constexpr uint16_t DEFAULT_FPV_PREARM_INTERVAL_MS = 3000;

    void begin(Stream &serial); void update(); void setRegistry(CameraRegistry *reg) { _registry = reg; } void setCamera(Camera *cam, const CameraData *data) { _camera = cam; _cameraData = data; } const Config &config() const { return _cfg; } void processCommand(const char *line, Stream &out);
    void setCameraType(uint8_t v); void setDisarmDelay(uint32_t ms); void setStopOnDisarm(bool v); void setAuxChannel(uint8_t ch); void setAuxMode(uint8_t mode); void setCameraMatchMode(uint8_t v); void setCameraWakeGuard(bool v); void setDebugBle(bool v); void setLowPowerMode(bool v); void setWifiApStartDelay(uint32_t sec); void setWifiApEnabled(bool v); void setOsdTemplate(uint8_t n, const char *tpl); void setBf45Compat(bool v); void setPilotNameEnabled(bool v); void setPilotNameTemplate(const char *tpl); void setCraftNameEnabled(bool v); void setCraftNameTemplate(const char *tpl); void setFpvStateMode(bool v); void setFpvErrorEnabled(bool v); void setFpvErrorText(const char *text); void setFpvReadyEnabled(bool v); void setFpvReadyText(const char *text); void setFpvRecordingEnabled(bool v); void setFpvRecordingText(const char *text); void setFpvRecFlash(bool v); void setFpvLowBatteryEnabled(bool v); void setFpvLowBatteryPct(uint8_t pct); void setFpvLowBatteryReadyFlash(bool v); void setFpvLowBatteryRecText(bool v); void setFpvLowBatteryText(const char *text); void setFpvLowRecTimeEnabled(bool v); void setFpvLowRecTimeMin(uint16_t mins); void setFpvLowRecReadyWarning(bool v); void setFpvLowRecRecordingWarning(bool v); void setFpvLowRecTimeText(const char *text); void setFpvHotWarningEnabled(bool v); void setFpvHotReadyWarning(bool v); void setFpvHotRecordingWarning(bool v); void setFpvHotWarningText(const char *text); void setFpvPreArmReminderEnabled(bool v); void setFpvPreArmReminderText(const char *text); void setFpvPreArmReminderShowMs(uint16_t ms); void setFpvPreArmReminderIntervalMs(uint16_t ms); bool setCaddxSsid(const char *ssid); bool setCaddxPass(const char *pass);
private:
    void load(); void save(); void printAll(Stream &out); void handleLine(const char *line, Stream &out); void handleCamerasCmd(const char *sub, Stream &out); void handleWifiCmd(const char *sub, Stream &out); Preferences _prefs; Config _cfg{}; CameraRegistry *_registry = nullptr; Camera *_camera = nullptr; const CameraData *_cameraData = nullptr; Stream *_serial = nullptr; char _buf[80]; uint8_t _len = 0;
};
