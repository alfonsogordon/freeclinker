> [!IMPORTANT]
> # 🚀 THIS PROJECT HAS MOVED TO FPV CAMBUDDY
> **FreeCLinker — FPSteVe Edition is now the legacy version.**
>
> Active development, new features and current documentation have moved to **FPV CamBuddy**.
>
> **➡️ [GO TO FPV CAMBUDDY](https://alfonsogordon.github.io/FPV-CamBuddy/)**  
> **➡️ [FPV CAMBUDDY GITHUB](https://github.com/alfonsogordon/FPV-CamBuddy)**

# FreeCLinker — FPSteVe Edition Quick Start

The simple route from a fresh **ESP32-C3 Super Mini** to automatic GoPro recording and camera status in your Betaflight OSD.

> FPSteVe Edition is based on **[FreeCLinker by sheeprine](https://github.com/sheeprine/freeclinker)**. You can also visit the [original FreeCLinker project site](https://sheeprine.github.io/freeclinker/).

**No CLI setup is required for the normal FPSteVe Edition setup.** Flash it in the browser, configure it in FPSteVe Easy Config, then set up the flight-controller UART and OSD in Betaflight Configurator.

## 1. Flash FreeCLinker

Open the **FPSteVe Edition Web Flasher**:

https://alfonsogordon.github.io/freeclinker/flash.html

Connect your ESP32-C3 Super Mini by USB and install the current FPSteVe Edition firmware.

When flashing finishes, **power-cycle the C3 once** — unplug/replug USB or cycle the quad/board power.

Then open **FPSteVe Easy Config**:

https://alfonsogordon.github.io/freeclinker/config.html

## 2. Configure it in the browser

Connect to the C3 from FPSteVe Easy Config. Your current settings should be read automatically.

A successful read shows:

**🤘 All settings read from C3 ✓**

For most GoPro FPV setups, the fresh defaults are already sensible. They include:

- automatic recording when you arm
- stopping recording **5 seconds after disarm**
- GoPro auto-connect/reconnect
- low-power BLE
- camera status in the OSD
- REC-only while armed and recording
- flashing REC
- first-arm **CLEAN LENS** reminder
- camera warnings

Change anything you want in the web configurator, then press the single **SAVE / APPLY SETTINGS** button.

When everything has been written and read back successfully you'll see:

**🤘 All settings saved and verified on C3 ✓**

That's the C3 configuration done. You do not need to copy settings into a terminal or use Betaflight CLI commands.

## 3. Connect the C3 to your flight controller

FreeCLinker needs one spare flight-controller UART.

For the standard ESP32-C3 Super Mini setup:

| C3 connection | Flight controller |
|---|---|
| **GPIO4 / TX** | UART **RX** |
| **GPIO5 / RX** | UART **TX** |
| **GND** | GND |
| **5V** | suitable 5V supply |

Remember: **TX goes to RX and RX goes to TX**, and the C3 and FC need a common ground.

Board layouts vary between ESP32-C3 Super Mini manufacturers, so use the labels/pinout supplied with **your actual board** rather than relying on a generic board drawing.

## 4. Set up the UART in Betaflight Configurator

Open **Betaflight Configurator → Ports**.

Find the UART you wired to the C3 and enable **MSP** for that UART. FreeCLinker uses **115200 baud**.

Save and reboot the flight controller.

There is no normal FreeCLinker CLI step — the rest of the FreeCLinker options are set from **FPSteVe Easy Config**.

## 5. Choose your OSD method

In **FPSteVe Easy Config**, choose the method matching your Betaflight version.

### Betaflight 4.5

Choose the **BF 4.5 / Pilot & Craft Name** method.

Pilot Name is enabled by default. In **Betaflight Configurator → OSD**, enable/place the **Pilot Name** element where you want the camera information to appear.

Craft Name is optional and can be enabled in FPSteVe Easy Config if you want a second camera-information line; if you use it, place the **Craft Name** OSD element too.

This is the path physically tested for FPSteVe Edition V1.

### Betaflight 2026.6+

Choose **BF 2026.6+ — Custom Messages 1–4**.

The four messages are already configured with the FPSteVe defaults. In **Betaflight Configurator → OSD**, enable/place the Custom Message elements you want to use.

This newer path is implemented and tested through the integrated OSD Preview/firmware logic, but has **not yet been physically tested against a flight controller running BF 2026.6+**.

## 6. Power up the GoPro

With the normal defaults, there is no separate connection routine to perform every time you fly.

Power the quad/FreeCLinker and make sure the GoPro is awake and available. **FreeCLinker should automatically find and connect to it on the first normal power-up.** It should then reconnect automatically on later power-ups whenever that camera is available.

When switching to a GoPro that FreeCLinker has **not paired with before**, you may need to open that camera's **Pair** menu for the first connection. As one example from V1 testing, after a HERO11 Black Mini had already been connected, a MAX2 needed to be put into its Pair menu the first time it was used. **Those two camera models are examples of the observed pairing behaviour, not a requirement or limitation to those specific models.** Once paired, normal automatic connection/reconnection can resume.

With **Wake Guard** enabled, FreeCLinker will not deliberately wake a sleeping GoPro just by scanning. If the GoPro is asleep, wake it normally and FreeCLinker should connect automatically.

In the OSD you may briefly see **ERR** while the camera is unavailable. Once the GoPro is connected and ready, the status becomes **RDY**.

## 7. Check it before flying

Do this once on the bench with the props removed:

1. Power the quad and wake the GoPro.
2. Check that FreeCLinker connects automatically and the OSD reaches **RDY**.
3. Before the first arm, the default **CLEAN LENS** reminder should appear.
4. Arm the quad. The GoPro should start recording and the OSD should show the default flashing **REC** behaviour.
5. Disarm. Your normal OSD should return immediately while the GoPro continues recording for the configured delay.
6. After the default **5 seconds**, recording should stop and the OSD should return to **RDY**.

If that works, the normal setup is complete. 🤘

## Want to change the behaviour?

Use **FPSteVe Easy Config**. It contains the camera, recording, OSD, warnings, AUX and connection settings in one place, plus the integrated **OSD Preview** so you can see most OSD changes before trying them on the quad.

You shouldn't need to edit CLI values for normal use.

## Help & feedback

Need help? Join the **Squadding Quads Discord** and ask for **FPSteVe**: https://discord.gg/eE6DkgEnjU

When asking for help, the most useful details are your **camera model, Betaflight version, C3 board and what the OSD is displaying**.

---

**FPSteVe Edition V1.0** 🤘
