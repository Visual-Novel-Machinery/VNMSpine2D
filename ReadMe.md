# Visual Novel Machinery Spine2D Integration
This is the Spine2D integration for Visual Novel Machinery.

If you intend to use this in your project you need to have your own [Spine license](https://esotericsoftware.com/spine-purchase). **DO NOT USE THIS WITHOUT THE LICENSE!**

## Setup
1. Follow the instructions [here](https://github.com/EsotericSoftware/spine-runtimes/blob/4.1/spine-ue4/README.md#usage) to install the Spine Plugin into your project.
2. Add a folder in your Plugins folder called VisualNovelMachinerySpine2D.
3. Copy the contents of this repository into the folder you just created.
4. Start your Unreal Engine Project. On Start Up it will ask you to build the new plugins. Do so.

## Usage
1. Open the CharacterDisplayWidget blueprint
2. Click on File -> Reparent Blueprint.
3. Reparent the widget blueprint to BaseSpine2DCharacterDisplayWidget.
4. Add a Spine Widget right next the Character Image and call it "SpineCharacterImage"