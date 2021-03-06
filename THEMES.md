Themes
======

EmulationStation allows each system to have its own "theme." A theme is a collection of display settings and images defined in an XML document.

ES will check two places for a theme: first, the system's search directory for theme.xml. Then, if that's not found, $HOME/.emulationstation/es_theme.xml.

Almost all positions, dimensions, etc. work in percentages - that is, they are a decimal between 0 and 1, representing the percentage of the screen on that axis to use.
This ensures that themes look similar at every resolution.


Example
=======

Here's a simple theme that defines some colors and displays a background:
```
<theme>
	<listPrimaryColor>0000FF</listPrimaryColor>
	<listSecondaryColor>00FF00</listSecondaryColor>

	<component>
		<type>image</type>
		<path>./theme/background.png</path>
		<pos>0 0</pos>
		<dim>1 1</dim>
		<origin>0 0</origin>
	</component>
</theme>
```

All themes must be enclosed in a `<theme>` tag.


Components
==========
A theme is made up of components, which have various types. At the moment, the only type is `image`. Components are rendered in the order they are defined - that means you'll want to define the background first, a header image second, etc.


The "image" component
=====================
Used to display an image.

`<path>` - path to the image file. Most common file types are supported, and . and ~ are properly expanded.

`<pos>` - the position, as two screen percentages, at which to display the image.

`<dim>` - the dimensions, as two screen percentages, that the image will be resized to. Make one axis 0 to keep the aspect ratio.

`<origin>` - the point on the image that `<pos>` defines, as an image percentage. "0.5 0.5", the center of the image, by default.

`<tiled />` - if present, the image is tiled instead of resized. A smaller image tiled many times is **slower** than a larger immage tiled few times.


Display tags
============
Display tags must be at the root of the <theme> tree - for example, they can't be inside a component tag. They are not required.

`<listPrimaryColor>` - the hex font color to use for games on the GuiGameList.

`<listSecondaryColor>` - the hex font color to use for folders on the GuiGameList.

`<descColor>` - the hex font color to use for the description on the GuiGameList.

`<listSelectorColor>` - the hex color to use for the "selector bar" on the GuiGameList.

`<listSelectedColor>` - the hex color to use for selected text on the GuiGameList. Default is -1, which will not change the color.

`<listLeftAlign />` - if present, the games list names will be left aligned to the value of `<listOffsetX>` (default 0.5).

`<hideHeader />` - if present, the system name header won't be displayed (useful for replacing it with an image).

`<hideDividers />` - if present, the divider between games on the detailed GuiGameList won't be displayed.

`<listOffsetX>` - the percentage to offset the list by. Default is 0.5 (half the screen). **Will also move the selector bar**.

`<listTextOffsetX>` - the percentage to offset the text in the list by. Default is 0.005. Only works in combination with `<listLeftAlign />`.

`<gameImageOffsetY>` - the percentage to offset the displayed game image by. Default is the height of the header font.

List of variables
=================

Variables can be used in position and dimension definitions. They can be added, subtracted, multiplied, and divided. Parenthesis are valid. They are a percentage of the screen.

`$headerHeight` - height of the system name header.

`$infoWidth` - where the center of the horizontal divider is drawn.


-Aloshi
http://www.aloshi.com
