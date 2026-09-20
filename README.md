> [!IMPORTANT]
> # 🚀 THIS PROJECT HAS MOVED TO FPV CAMBUDDY
> **FreeCLinker — FPSteVe Edition is now the legacy version.**
>
> Active development, new features and current documentation have moved to **FPV CamBuddy**.
>
> **➡️ [GO TO FPV CAMBUDDY](https://alfonsogordon.github.io/FPV-CamBuddy/)**  
> **➡️ [FPV CAMBUDDY GITHUB](https://github.com/alfonsogordon/FPV-CamBuddy)**

# FreeCLinker — FPSteVe Edition

**Automatic action-camera control and Betaflight OSD telemetry from an ESP32-C3 Super Mini.**

> **Based on the original [FreeCLinker by sheeprine](https://github.com/sheeprine/freeclinker).** Visit the [original FreeCLinker project site](https://sheeprine.github.io/freeclinker/) for the upstream project, its supported-camera foundations and original documentation.

FreeCLinker connects a supported action camera to your flight controller without adding another control to your pre-flight routine. Power the quad, let the C3 find the camera, arm and fly. Recording can start automatically on arm and stop after a configurable delay on disarm, while camera status is shown directly in the Betaflight OSD.

FPSteVe Edition builds on that foundation with a simplified configurator, GoPro-focused flight behaviour, richer OSD, warnings, automatic recording and extensive bench/flight testing.

## Start here

- **Configurator:** https://alfonsogordon.github.io/freeclinker/config.html
- **Web flasher:** https://alfonsogordon.github.io/freeclinker/flash.html
- **Quick start:** [QUICKSTART.md](QUICKSTART.md)
- **Project website:** https://alfonsogordon.github.io/freeclinker/

## Supported cameras

FreeCLinker includes camera backends/support paths for:

- **GoPro**
- **DJI Action**
- **Sony**
- **Blackmagic**
- **Insta360**
- **Caddx**

**FPSteVe Edition hardware-tested:** GoPro HERO11 Black Mini and GoPro MAX2.

The other camera families are supported by the FreeCLinker firmware foundations/backends but have **not necessarily been physically validated by FPSteVe**. Protocol capabilities and available OSD telemetry can vary by camera family and model.

## See the OSD in action

The project homepage includes a compact animated demonstration using the same background image and **BF 4.5 Pilot Name default** as the integrated Easy Config OSD Preview: **ERR → RDY → CLEAN LENS → ARM/flashing REC → DISARM/full Pilot line while the camera is still recording → delayed stop → RDY**.

You can exercise the same behaviour interactively in the **OSD Preview** inside the configurator.

## What it does

### Camera control
- **GoPro, DJI Action, Sony, Blackmagic, Insta360 and Caddx camera support paths**
- Automatic camera discovery and reconnect
- GoPro BLE control with wake/sleep-aware connection behaviour
- Start recording automatically when Betaflight arms
- Configurable delayed stop after disarm — **5 seconds by default**
- Optional AUX camera-mode control
- GoPro Burst Slo-Mo support through AUX while recording
- GoPro BLE keepalive while connected
- Camera matching for multi-camera setups
- Low-power radio mode to reduce RF output near the flight-control/RC system

### Betaflight OSD
- Camera state: **ERR / RDY / REC**
- Camera battery percentage
- Recording duration
- Remaining recording time/capacity where reported by the camera
- Camera mode, resolution, frame rate and stabilisation telemetry where available
- Configurable OSD templates/tokens
- **REC-only while armed + recording** for a clean flight display
- Optional **1 Hz flashing REC**
- First-arm temporary reminder — default **CLEAN LENS**
- Camera warnings: **BATT LOW / REC LOW / CAM HOT**
- Warning → temporary message → REC-only → normal OSD priority handling

### Betaflight compatibility
- **Betaflight 4.5:** Pilot Name / Craft Name compatibility mode
- **Betaflight 2026.6+:** Custom Messages 1–4 support
- Automatic arm-state polling over MSP
- Configurable UART/AUX integration

### FPSteVe Easy Config
- Browser-based configuration over USB
- Automatic settings read when connected
- One **SAVE / APPLY SETTINGS** action for the complete configuration
- Read-back verification after saving
- Settings stored on the C3 and retained across power cycles
- Integrated live OSD Preview
- Preview controls for ARM, recording, camera errors/hot state and first-arm reset
- Fresh-board defaults designed to be useful without a long setup session

### Flashing & board behaviour
- Browser-based ESP32-C3 flashing
- Clear post-flash power-cycle/configuration flow
- Wi-Fi AP configuration remains available as an optional/fallback feature
- BOOT-button force-AP recovery
- Status LED for scanning/connection/AP state

## Default OSD setup

FPSteVe Edition ships with sensible flight defaults. On **BF 4.5**, Pilot Name is enabled by default with:

`{stateonly} {batt} {rectf}`

On **BF 2026.6+**, the four Custom Message defaults are:

| Message | Default template |
|---|---|
| 1 | `{batt}` |
| 2 | `{state} {recdur}` |
| 3 | `{mode} {res} {fps} {eis}` |
| 4 | `{rectf} {rcap}` |

REC-only, flashing REC, CLEAN LENS and camera warnings are enabled by default on a fresh FPSteVe Edition configuration.

## Tested for V1 🤘

The following have been physically confirmed on the FPSteVe Edition hardware-test setup using **GoPro HERO11 Black Mini and GoPro MAX2**:

- ESP32-C3 Super Mini + GoPro BLE connection and automatic reconnect
- GoPro control from a real Betaflight 4.5 flight controller
- ARM → automatic recording
- DISARM → immediate normal OSD restoration → 5-second delayed recording stop → RDY
- BF 4.5 Pilot/Craft OSD output and live **ERR / RDY / REC** state
- REC-only while armed + recording, including flashing REC
- First-arm **CLEAN LENS** behaviour
- Configurator read, save, read-back verification and settings persistence after reconnect/power cycle
- GoPro keepalive: camera stays connected while FreeCLinker is powered and returns to normal camera auto-power-off behaviour when FreeCLinker is removed
- Web flasher and post-flash configuration flow

Camera-warning behaviour and priority have been validated in the integrated Preview/firmware logic; individual warning conditions have not all been forced on the installed flight-test camera.

## Implemented, but not yet hardware-tested

**Betaflight 2026.6+ Custom Messages 1–4** are implemented and exercised through the FPSteVe OSD Preview/firmware logic, but have **not yet been physically tested against a flight controller running that Betaflight generation**. The V1 hardware available for testing currently runs Betaflight 4.5, so this distinction is intentional.

Camera-family support beyond the GoPro models listed above has not necessarily been physically validated by FPSteVe. Some telemetry fields also depend on what a particular camera/model reports over its protocol.

## Quick hardware connection

Default ESP32-C3 Super Mini ↔ flight-controller UART wiring:

| C3 | Flight controller |
|---|---|
| GPIO4 TX | UART RX |
| GPIO5 RX | UART TX |
| GND | GND |
| 5V | suitable 5V supply |

MSP UART speed: **115200 baud**.

See the [Quick Start Guide](QUICKSTART.md) before powering the installation.

## GoPro pairing note

When switching to a GoPro that FreeCLinker has not paired with before, you may need to open that camera's **Pair** menu for the first connection. As one example from V1 testing, after a HERO11 Black Mini had already been connected, a MAX2 needed to be placed in its Pair menu the first time it was used. **The HERO11 Black Mini and MAX2 are examples of the observed behaviour, not a requirement or limitation to those specific models.** Once paired, normal automatic connection/reconnection can resume.

## Help & feedback

Need help? Join the **Squadding Quads Discord** and ask for **FPSteVe**: https://discord.gg/eE6DkgEnjU

Bug reports and useful real-world compatibility results are especially welcome — please include the camera model, Betaflight version and C3 board where possible.

## Credits

FPSteVe Edition is based on **[FreeCLinker by sheeprine](https://github.com/sheeprine/freeclinker)** and retains the work and supported-camera foundations of the upstream project. Thanks to the original FreeCLinker contributors and the camera/protocol projects that make this possible.

---

💜 **No donation link here.** If you like the project and feel like giving something back, take whatever you would've donated and spend it on more props 🤘 — or, even better, donate it to a local charity of your choice.

**FPSteVe Edition V1.0** 🤘
