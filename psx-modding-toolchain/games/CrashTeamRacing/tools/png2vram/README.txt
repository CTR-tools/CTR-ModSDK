Usage:
Put the PNG of your new 4bpp textures in the newtex/ folder, and call main.py
The names of the texture must follow the CTR-Tools standard: x_y_palx_paly_w_h.png
The tool will output C structures that you can use to load the textures to VRAM, using the LoadImage method.
Look at the RetroFueled mod sample to see an example of this tool being in use.

Python tool created by TheRedhotbr

For 8bpp and 16bpp images, open main.py in notepad and change "bpp = 4" to "bpp = 8" or "bpp = 16".