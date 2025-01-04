# ue4-realtime-delay
## Overview
* This plugin enables Unreal Engine 4 and Unreal Engine 5 to run Delay without being affected by Global Time Dilation or Game Pause.
* The actual waiting time in the Delay node depends on the Global Time Dilation setting, or it waits indefinitely during Game Pause, making it difficult to use in some cases.
* With the Realtime Delay node provided by this plug-in, the delay will be performed at the specified time.

## Specification

* Provides a "Realtime Delay" node that can execute Delay without being affected by Global Time Dilation or Game Pause

## Supported Environment

* UE4.26 - UE4.27
* UE5.0 - UE5.4

I believe it will work with most UE4 and UE5 versions as only basic functionality is used. It would be great if you could give me a running report.

## Usage

1. Put Plugins/RealtimeDelay in the Plugins folder of your project
1. Place a Realtime Delay node where you want to Delay as shown below
![](images/image.png)

## License
MIT

## Update History
* 2024/01/04 v0.1.2 Fixes bugs
  * Fixed to wait for at least one Tick even if the time specified is less than Tick interval
* 2024/07/11 v0.1.1 Fixes bugs
  * Fixed a bug that could cause a memory access violation if an object was destroyed during Realtime Delay execution
* 2023/08/19 v0.1.0 released
