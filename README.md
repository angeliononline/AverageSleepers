# Average Sleepers Audio Plugin

## Overview

The Average Sleepers Audio Plugin is a simple audio effect that visualizes the voltage levels of each channel in a multi-channel audio stream, inspired by the Expert Sleepers Silent Way ES-5 Controller. This plugin offers a more accessible and visually based version of the ES-5 Controller, making it easier to monitor the voltage levels of your audio channels. The plugin works with up to 8 channels and displays the voltage levels using different colors for positive, negative, and zero voltages.

This plugin is built using the JUCE framework and can be used as a VST or AU plugin in various Digital Audio Workstations (DAWs) such as Ableton Live, Logic Pro, and others.

## Features

- Visualizes the voltage levels of up to 8 channels in real-time, inspired by the Expert Sleepers Silent Way ES-5 Controller
- Offers a more accessible and visually based version of the ES-5 Controller for easier voltage level monitoring
- Different colors for positive, negative, and zero voltage levels
- Compatible with VST and AU plugin formats

## Building the Plugin

### Prerequisites

- Download and install the [JUCE](https://juce.com/get-juce) framework
- [Xcode](https://apps.apple.com/us/app/xcode/id497799835) for macOS or [Visual Studio](https://visualstudio.microsoft.com/downloads/) for Windows

### Build Steps

1. Clone or download this repository
2. Open the `.jucer` project file in the Projucer application (part of the JUCE framework)
3. In Projucer, set the proper paths for JUCE modules and the VST/AU SDKs if needed
4. Save and open the project in your preferred IDE (Xcode or Visual Studio)
5. Build the project using the IDE
6. The compiled plugin (VST or AU) will be located in the build folder

## Usage

1. Install the compiled plugin (VST or AU) in the appropriate plugin directory for your DAW
2. Open your DAW and add the Average Sleepers Audio Plugin as an audio effect on a track or bus
3. Play multi-channel audio through the plugin and observe the real-time visualization of the voltage levels

## License

This project is licensed under the GNU General Public License v3.0. See the [LICENSE](LICENSE) file for more information.

## Contributing

Feel free to submit pull requests or open issues if you'd like to contribute to the development of this plugin.
