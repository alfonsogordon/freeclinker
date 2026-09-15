# FPV CamBuddy · by FPSteVe — Quick Start

This guide covers both the proven single-camera setup and the **V1.0.2 experimental Multi Cam workflow** on an ESP32-C3 Super Mini.

> **This file is from the `experimental` branch.** Stable V1.0.1 remains on `main`.
>
> Multi Cam and advanced BLE power are development features. **Bench test with props removed before flight.**

> FPV CamBuddy is based on **[FreeCLinker by sheeprine](https://github.com/sheeprine/freeclinker)**. You can also visit the [original FreeCLinker project site](https://sheeprine.github.io/freeclinker/).

For a full explanation of every V1.0.2 experimental feature, see [EXPERIMENTAL_V1.0.2.md](EXPERIMENTAL_V1.0.2.md).

## 1. Flash the correct firmware

For V1.0.2 testing, use the **FPV CamBuddy Flasher**:

https://alfonsogordon.github.io/freeclinker/experimental/flash.html

Connect the ESP32-C3 Super Mini by USB and install the latest experimental build.

When flashing finishes, **power-cycle the C3 once**.

Then open **FPV CamBuddy Config**:

https://alfonsogordon.github.io/freeclinker/experimental/config.html

Do not use the stable flasher/configurator when you are specifically testing V1.0.2 Multi Cam features.

## 2. Connect and read settings

Connect to the C3 from FPV CamBuddy Config and use **Read Settings**.

Confirm the connected board reports **V1.0.2** before relying on the V1.0.2-only controls.

The C3 is the source of truth. The configurator reads the board values, and save/apply writes them back and verifies them.

## 3. Prove the normal single-camera workflow first

Before enabling Multi Cam, prove that the basic camera path still works on the V1.0.2 binary.

For a normal GoPro setup, check:

- automatic connection/reconnect
- ARM starts recording
- DISARM restores the normal OSD immediately
- recording stops after the configured delay — **5 seconds by default**
- OSD moves through **ERR / RDY / REC** correctly
- REC-only / flashing REC behaves as expected if enabled

This gives you a known-good baseline before adding multi-camera complexity.

## 4. Connect the C3 to your flight controller

FPV CamBuddy needs one spare flight-controller UART.

For the standard ESP32-C3 Super Mini setup:

| C3 connection | Flight controller |
|---|---|
| **GPIO4 / TX** | UART **RX** |
| **GPIO5 / RX** | UART **TX** |
| **GND** | GND |
| **5V** | suitable 5V supply |

Remember: **TX goes to RX and RX goes to TX**, and the C3 and FC need a common ground.

Board layouts vary, so confirm the labels/pinout for your actual C3 board.

## 5. Set up the UART in Betaflight

Open **Betaflight Configurator → Ports**.

Find the UART wired to the C3 and enable **MSP**. FPV CamBuddy uses **115200 baud**.

Save and reboot the flight controller.

## 6. Choose your OSD method

### Betaflight 4.5

Choose the **Pilot / Craft Name** compatibility method.

Pilot Name is enabled by default. Place the **Pilot Name** OSD element where you want camera information to appear.

Craft Name is optional.

This is the path physically tested during V1 development.

### Betaflight 2026.6+

Choose **Custom Messages 1–4**.

The default templates are already populated in the configurator. Place the Custom Message elements you want in Betaflight OSD.

This path is implemented and exercised in the firmware/preview flow but has not yet been physically accepted on a BF 2026.6+ flight controller.

## 7. Enable the experimental UI

At the top of FPV CamBuddy Config, turn on **Experimental**.

The yellow **Experimental Multi Cam Settings** section should appear.

The UI is intentionally nested:

- Experimental OFF → the whole Multi Cam section is hidden
- Experimental ON → Multi Cam can be enabled
- Multi Cam OFF → advanced Multi Cam controls stay hidden
- Multi Cam ON → BLE power-profile option appears
- BLE power profile ON → power/timing controls appear

## 8. Enable Multi Cam

Turn on **Enable Multi Cam coordinator**.

The coordinator currently contains support paths for:

- GoPro
- DJI Action
- Sony
- Blackmagic
- Insta360
- Caddx

A reboot is recommended after changing the Multi Cam mode so the correct camera backend/coordinator is selected cleanly from startup.

### First-time GoPro setup

For the **first connection of each GoPro in Multi Cam mode, connect the cameras one at a time**:

1. Power on the first GoPro and let FPV CamBuddy discover/connect to it and save it.
2. Then power on the second GoPro and let FPV CamBuddy discover/connect to that one.
3. Repeat for any additional GoPros.

After each GoPro has been learned/saved once, they can be powered together and Multi Cam will reconnect to the saved cameras automatically on later boots.

If a GoPro has never been paired with FPV CamBuddy before, you may also need to open that camera's **Pair** menu for its initial connection.

### What ARM/DISARM means in Multi Cam

ARM requests START from connected cameras.

DISARM follows the normal configured stop delay, then requests STOP.

If a camera joins or reconnects later, FPV CamBuddy attempts to reconcile that camera to the current desired state:

- currently recording → send START
- currently stopped → send STOP

This is designed to recover a second camera that temporarily leaves Bluetooth range.

## 9. Start with two cameras

Do not jump straight to the maximum possible count.

Start with **two nearby cameras** and confirm:

1. both are discovered/connected;
2. the C3 LED reflects two connected cameras;
3. ARM starts both;
4. OSD reaches `REC 2/2` when both recording states are confirmed;
5. DISARM and the configured delay stop both;
6. a camera leaving and re-entering range is reconciled correctly.

The experimental Multi-GoPro backend has **8 application slots**, but real simultaneous connection count can be lower because of ESP32 Bluetooth resources, stack configuration, scanning and memory.

## 10. Understand the multi-camera OSD

V1.0.2 can show aggregate camera state.

Examples:

- `REC 2/2` — two connected and both confirmed recording
- `PART 1/2` — two connected but only one confirmed recording

The `{cams}` token is also available.

Where recording-state counts are confirmed it represents:

`recording/connected`

For example `2/2`.

The coordinator also combines available telemetry conservatively: lowest battery, lowest remaining recording time and hottest reported camera state.

## 11. Check the status LED

With Multi Cam enabled:

- one connected camera keeps the normal steady-connected indication;
- more than one camera produces a short pulse count in a repeating three-second period.

Examples:

- 2 cameras → 2 pulses
- 3 cameras → 3 pulses

Use this as a quick visual sanity check before arming.

## 12. Only then test Advanced BLE Power

Once basic Multi Cam operation is reliable, enable **Multi Cam BLE power profile**.

The sequence is:

**Idle / disarmed → Arm boost → Armed → Disarm boost → Idle**

Available configured power steps are:

- -12 dBm
- -9 dBm
- -6 dBm
- -3 dBm
- 0 dBm
- +3 dBm
- +6 dBm
- +9 dBm

A sensible first bench-test profile is:

| Stage | Suggested first test |
|---|---|
| Idle / disarmed | +9 dBm |
| Arm boost | +9 dBm |
| Arm boost duration | 1500–3000 ms |
| Armed | -6 or -9 dBm initially |
| Disarm boost | +9 dBm |
| Disarm boost duration | 1500–3000 ms |

Only move to -12 dBm armed once you have proved command/reconnect reliability for your camera placement.

A boost duration of `0 ms` skips that boost phase.

## 13. Optional: only activate the power profile after multiple cameras

**Only after multiple cameras detected** leaves normal Low Power behaviour alone until the coordinator has observed more than one connected camera.

Once triggered, the condition is latched until reboot. It intentionally does not switch off again when a second camera briefly disconnects.

## 14. Bench-test reconnect behaviour

With props removed, test these cases deliberately:

1. both cameras connected while stopped;
2. ARM and confirm both start;
3. move/turn off the second camera so it disconnects;
4. reconnect it while still armed and check it is sent START;
5. DISARM and allow the normal stop delay to expire;
6. disconnect/reconnect the second camera while the desired state is stopped and check STOP is reconciled.

Also watch the OSD and LED count during each transition.

## 15. GoPro pairing note

A GoPro not previously paired with FPV CamBuddy may need its **Pair** menu opened for the initial connection.

In Multi Cam mode, **learn/save new GoPros one at a time on their first connection**. Once each camera has been saved, normal simultaneous automatic reconnect can resume on later boots.

During V1 testing, HERO11 Black Mini and MAX2 provided examples of pairing behaviour. Those models are examples, not a limitation to those specific cameras.

With Wake Guard enabled, FPV CamBuddy does not deliberately wake a sleeping GoPro just by scanning.

## 16. What is still experimental

Treat these as hardware-test items rather than proven flight behaviour:

- 2+ simultaneous BLE cameras
- 3+ camera scaling
- mixed camera families
- practical maximum C3 connection count
- reduced armed BLE power
- boost timing/reconnect performance
- partial command acknowledgement
- `REC x/y` / `PART x/y` on a real FC OSD
- LED pulse count in real installation conditions

A successful build means the code compiles; it does not prove RF reliability.

## Help & feedback

Need help? Join the **Squadding Quads Discord** and ask for **FPSteVe**:
https://discord.gg/eE6DkgEnjU

For V1.0.2 reports, include:

- camera make/model and quantity
- C3/ESP32 board
- Betaflight version
- BLE power values and boost timings
- camera placement / approximate distance
- OSD state/count
- LED pulse count
- whether reconnect START/STOP reconciliation worked

---

**FPV CamBuddy · by FPSteVe · V1.0.2 EXPERIMENTAL** 🤘
