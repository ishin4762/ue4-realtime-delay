# ue4-realtime-delay
## Overview
* This plugin enables Unreal Engine 4 and Unreal Engine 5 to run Delay without being affected by Global Time Dilation or Game Pause.
* The actual waiting time in the Delay node depends on the Global Time Dilation setting, or it waits indefinitely during Game Pause, making it difficult to use in some cases.
* With the Realtime Delay node provided by this plug-in, the delay will be performed at the specified time.

## Specification

* Provides a "Realtime Delay" node that can execute Delay without being affected by Global Time Dilation or Game Pause

## Supported Environment

* UE4.26.x
* UE5.2.x

I believe it will work with most UE4 and UE5 versions as only basic functionality is used. It would be great if you could give me a running report.

## Usage

1. Put Plugins/RealtimeDelay in the Plugins folder of your project
1. Place a Realtime Delay node where you want to Delay as shown below
![](images/image.png)

## Lincense
MIT

## Update History
* 2023/08/19 v0.1.0 released
