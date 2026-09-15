# FPV CamBuddy · by FPSteVe

**Automatic action-camera control and Betaflight OSD telemetry from an ESP32-C3 Super Mini.**

> **This is the `experimental` branch.** It currently contains the V1.0.2 development build. Stable V1.0.1 remains on `main`.
>
> **Bench test experimental firmware before flight.** Multi-camera and advanced BLE-power behaviour are implemented and building successfully, but still require real-world hardware validation.

> **FPV CamBuddy is based on the original [FreeCLinker by sheeprine](https://github.com/sheeprine/freeclinker).** Visit the [original FreeCLinker project site](https://sheeprine.github.io/freeclinker/) for the upstream project, its supported-camera foundations and original documentation.

FPV CamBuddy connects supported action cameras to your flight controller so camera recording can follow the quad automatically. Power the quad, let the C3 find the camera, arm and fly. Recording can start automatically on ARM and stop after a configurable delay on DISARM, while camera state and telemetry are shown in the Betaflight OSD.

FPV CamBuddy continues the development work previously released as FreeCLinker — FPSteVe Edition, including a simplified configurator, GoPro-focused flight behaviour, richer OSD, warnings, automatic recording, browser flashing and extensive bench/flight test tooling.

## Start here

### Experimental V1.0.2

- **FPV CamBuddy Config:** https://alfonsogordon.github.io/freeclinker/experimental/config.html
- **FPV CamBuddy Flasher:** https://alfonsogordon.github.io/freeclinker/experimental/flash.html
- **Full V1.0.2 feature guide:** [EXPERIMENTAL_V1.0.2.md](EXPERIMENTAL_V1.0.2.md)
- **Quick start:** [QUICKSTART.md](QUICKSTART.md)

### Stable V1.0.1

- Stable configurator: https://alfonsogordon.github.io/freeclinker/config.html
- Stable flasher: https://alfonsogordon.github.io/freeclinker/flash.html
- Stable source: https://github.com/alfonsogordon/freeclinker/tree/main

## Supported cameras

FPV CamBuddy includes camera backends/support paths for **GoPro, DJI Action, Sony, Blackmagic, Insta360 and Caddx**, based on the original FreeCLinker firmware foundations.

**FPSteVe hardware-tested:** GoPro HERO11 Black Mini and GoPro MAX2.

The other camera families are supported by the FreeCLinker firmware foundations/backends but have **not necessarily been physically validated by FPSteVe**. V1.0.2 Multi Cam operation across multiple or mixed camera families remains experimental hardware-test territory.

## V1.0.2 experimental highlights

### Multi Cam coordinator

V1.0.2 can use a coordinator instead of the normal single-camera backend. The coordinator includes support paths for:

- GoPro
- DJI Action
- Sony
- Blackmagic
- Insta360
- Caddx

With Multi Cam enabled, ARM/START and DISARM/STOP requests are sent across the coordinator rather than to one selected camera only.

A camera that joins or reconnects later is reconciled to the current requested state. If the quad currently wants recording, the camera is told to START; if the system currently wants stopped recording, the camera is told to STOP.

For **first-time Multi Cam setup with GoPros, connect and save new cameras one at a time**. Let the first GoPro connect and be learned before powering/connecting the next. After each GoPro has been saved once, they can be powered together and normal simultaneous automatic reconnect can resume on later boots. A completely new GoPro may also need its **Pair** menu opened for that first connection.

### Multi-GoPro

The experimental Multi-GoPro backend now has **8 bounded application slots** instead of the previous arbitrary six-camera limit.

Eight is not a guarantee of eight real simultaneous BLE connections. Actual usable count depends on ESP32 Bluetooth controller/host resources, stack configuration, scanning load, memory and camera behaviour.

### Multi-camera OSD

V1.0.2 adds aggregate camera counts and recording-state counts.

Typical compact states include:

- `REC 2/2` — two connected, both confirmed recording
- `PART 1/2` — two connected, only one confirmed recording

The `{cams}` token is also available for templates. Where recording counts are confirmed it represents `recording/connected`; otherwise it falls back to the connected count rather than presenting a false partial failure.

Aggregate multi-camera telemetry uses conservative values where available:

- lowest camera battery
- lowest remaining recording time
- hottest camera state
- combined media readiness

### Advanced BLE TX power profile

The experimental BLE profile supports four phases:

**Idle / disarmed → Arm boost → Armed → Disarm boost → Idle**

Available power steps are -12, -9, -6, -3, 0, +3, +6 and +9 dBm.

Each boost phase can be given a duration. A duration of `0 ms` skips that boost and preserves the earlier two-state armed/disarmed behaviour.

The optional **Only after multiple cameras detected** setting keeps normal Low Power behaviour until more than one connected camera has been observed. Once triggered, that power-profile latch remains active until reboot so it does not flap on/off when a second camera briefly disconnects.

### Status LED camera-count pulses

With Multi Cam enabled and more than one camera connected, the C3 status LED can show the connected-camera count as short pulses in a repeating three-second period.

- one connected camera: normal steady connected indication
- two cameras: two short pulses
- three cameras: three short pulses

Scanning and AP indications remain separate.

### FPV CamBuddy Config

V1.0.2 controls are grouped under **Experimental Multi Cam Settings**.

The UI is layered deliberately:

- Experimental master OFF → the whole V1.0.2 section is hidden
- Experimental master ON → Multi Cam can be enabled
- Multi Cam OFF → advanced Multi Cam controls remain hidden
- Multi Cam ON → BLE power-profile option becomes available
- BLE power profile ON → individual TX-power/timing settings become available

The connected C3 remains the source of truth. The configurator reads the actual settings from the board and saves/verifies them back to the board.

## Existing camera-control behaviour

When Multi Cam is disabled, the normal single-camera path remains in use.

Existing behaviour includes:

- automatic camera discovery and reconnect
- GoPro BLE control with wake/sleep-aware connection behaviour
- ARM starts recording automatically
- configurable delayed stop after DISARM — **5 seconds by default**
- optional AUX camera-mode control
- GoPro Burst Slo-Mo through AUX on the single-GoPro path
- GoPro BLE keepalive while connected
- camera matching
- normal Low Power BLE mode

The proven single-GoPro backend remains separate from the experimental coordinator.

## Betaflight OSD

Existing FPV CamBuddy OSD features include:

- camera state: **ERR / RDY / REC**
- camera battery percentage
- recording duration
- remaining recording time/capacity where reported
- mode, resolution, frame rate and stabilisation where available
- configurable OSD templates/tokens
- **REC-only while armed + recording**
- optional **1 Hz flashing REC**
- first-arm temporary reminder — default **CLEAN LENS**
- camera warnings: **BATT LOW / REC LOW / CAM HOT**
- Warning → Temporary Message → REC-only → normal OSD priority handling

### Betaflight compatibility

- **Betaflight 4.5:** Pilot Name / Craft Name compatibility mode
- **Betaflight 2026.6+:** Custom Messages 1–4 support
- automatic arm-state polling over MSP
- configurable UART/AUX integration

## Default OSD setup

On **BF 4.5**, Pilot Name is enabled by default with:

`{stateonly} {batt} {rectf}`

On **BF 2026.6+**, the four Custom Message defaults are:

| Message | Default template |
|---|---|
| 1 | `{batt}` |
| 2 | `{state} {recdur}` |
| 3 | `{mode} {res} {fps} {eis}` |
| 4 | `{rectf} {rcap}` |

REC-only, flashing REC, CLEAN LENS and camera warnings are enabled by default on a fresh FPV CamBuddy configuration.

## V1 hardware-confirmed behaviour 🤘

The following stable/single-camera behaviour has been physically confirmed using **GoPro HERO11 Black Mini and GoPro MAX2** on the FPSteVe development setup:

- ESP32-C3 Super Mini + GoPro BLE connection and automatic reconnect
- GoPro control from a real Betaflight 4.5 flight controller
- ARM → automatic recording
- DISARM → immediate normal OSD restoration → 5-second delayed recording stop → RDY
- BF 4.5 Pilot/Craft OSD output and live **ERR / RDY / REC** state
- REC-only while armed + recording, including flashing REC
- first-arm **CLEAN LENS** behaviour
- configurator read/save/read-back verification and settings persistence
- GoPro keepalive
- web flasher and post-flash configuration flow

## V1.0.2 implemented but still hardware-test territory

The experimental source builds successfully for both firmware targets, but these areas still need physical validation:

- simultaneous 2+ and especially 3+ BLE cameras
- practical ESP32-C3 simultaneous-connection ceiling
- mixed camera-family operation
- camera families beyond the GoPro models physically tested by FPSteVe
- reconnect/rejoin behaviour when a second camera leaves range
- delayed STOP reconciliation after reconnect
- advanced BLE power at -12/-9/-6 dBm in realistic camera positions
- ARM/DISARM boost timing on hardware
- partial recording acknowledgements
- multi-camera `REC x/y` and `PART x/y` OSD on a real FC
- LED camera-count pulses in actual use
- V1.0.2 regression bench test of the stable single-GoPro workflow

A successful compile is not proof of RF reliability. **Bench test with props removed first.**

## Quick hardware connection

Default ESP32-C3 Super Mini ↔ flight-controller UART wiring:

| C3 | Flight controller |
|---|---|
| GPIO4 TX | UART RX |
| GPIO5 RX | UART TX |
| GND | GND |
| 5V | suitable 5V supply |

MSP UART speed: **115200 baud**.

See [QUICKSTART.md](QUICKSTART.md) before powering the installation.

## GoPro pairing note

When switching to a GoPro that FPV CamBuddy has not paired with before, you may need to open that camera's **Pair** menu for the first connection. During V1 testing, a HERO11 Black Mini and MAX2 provided examples of this behaviour; those models are examples, not a restriction to those specific cameras.

In Multi Cam mode, **learn/save new GoPros one at a time on their first connection**. After each camera has been saved, normal automatic simultaneous reconnect can resume on later boots.

## Help & feedback

Need help? Join the **Squadding Quads Discord** and ask for **FPSteVe**:
https://discord.gg/eE6DkgEnjU

For experimental test reports, include the camera model(s), number of cameras, C3 board, Betaflight version, BLE power settings, camera placement/range and what the OSD/LED showed.

## Credits

**FreeCLinker — FPSteVe Edition has evolved into FPV CamBuddy.** FPV CamBuddy is based on **[FreeCLinker by sheeprine](https://github.com/sheeprine/freeclinker)** and retains the work and supported-camera foundations of the upstream project. Thanks to the original FreeCLinker contributors and the camera/protocol projects that make this possible.

---

💜 **No donation link here.** If you like the project and feel like giving something back, take whatever you would've donated and spend it on more props 🤘 — or, even better, donate it to a local charity of your choice.

**FPV CamBuddy · by FPSteVe · V1.0.2 EXPERIMENTAL** 🤘
