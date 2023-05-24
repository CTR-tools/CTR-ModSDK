from pathlib import Path, WindowsPath
from PIL import Image

p = Path("./niikasdtrack.png")

class scuffedpngtrack:
	def __init__(self, path: WindowsPath) -> None:
		self.img = (Image.open(p)).convert("RGB")
		self.img_width, self.img_height = self.img.size
		self.qb_size = 0x300
		self.qb_index = 0
		self.qb_posX = 0
		self.qb_posZ = 0
		self.offsetX = 0
		self.offsetZ = 0

	# so uhhhhh the way this works is I need the track's starting line to be at 0,0
	# so I need to find a way to calculate the 0,0 position in the track
	# so I'm gonna find a red dot in the png and then I'll self.offset the entirety of the track based on the location of that
	def get_start_coordinate(self) -> None:
		for x in range(self.img_width):
			for y in range(self.img_height):
				if self.img.getpixel((x, y)) == (255, 0, 0):
					self.offsetX, self.offsetY = (x, y)

	def export_as_c(self) -> None:
		x = 0
		y = 0
		buffer = "evil\n\n"
		for px in list(self.img.getdata()):
			if self.img.getpixel((x, y)) != (0, 0, 0):
				buffer += ("NEW_BLOCK(" + str(self.qb_index) + ", group4_ground, " + f"0x{self.qb_posX:x}" + ", " + f"0x{self.qb_posZ:x}" + ", NULL, 0x1800, 0xFF, 0x0, 0x0),").replace("0x-", "-0x")
				self.qb_index += 1
			else:
				buffer += "                                                                           "

			x += 1
			if x > self.img_width-1:
				buffer += "\n"
				x = 0
				y += 1

			print(f"{self.qb_index} offsetX: {self.offsetX}")
			print(f"{self.qb_index} image X: {x}")
			print(f"{self.qb_index} offsetZ: {self.offsetZ}")
			print(f"{self.qb_index} image Y: {y}")
			print(f"{self.qb_index} image X - offsetX: {x - self.offsetX}")
			print(f"{self.qb_index} image Y - offsetZ: {y - self.offsetZ}")
			self.qb_posX = (self.qb_size * (x - self.offsetX))
			self.qb_posZ = (self.qb_size * (y - self.offsetZ))
			print(f"{self.qb_index} qb_posX: {self.qb_posX}")
			print(f"{self.qb_index} qb_posZ: {self.qb_posZ}")
		
		filepath = Path(str(p) + "test.c")
		with open(filepath, "w") as file:
			file.write(buffer)

thing = scuffedpngtrack(p)
thing.get_start_coordinate()
thing.export_as_c()