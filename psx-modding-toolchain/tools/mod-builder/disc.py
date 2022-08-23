from common import DISC_PATH

import json

class DiscFile:
    def __init__(self, metadata: dict, physical_file: str) -> None:
        self.address = int(metadata["address"], 0)
        self.offset = int(metadata["offset"], 0)
        self.physical_file = physical_file.replace("\\", "/")


class Disc:
    def __init__(self, version) -> None:
        self.df_by_name = dict()
        with open(DISC_PATH, "r") as file:
            data = json.load(file)
            if "common" in data:
                self.read_data_container(data["common"])
            self.read_data_container(data[version])

    def read_data_container(self, data: dict) -> None:
        for file in data:
            for filename in file.keys():
                for section in file[filename]:
                    name = section["name"]
                    df = DiscFile(section, filename)
                    self.df_by_name[name] = df

    def get_df(self, name: str) -> DiscFile:
        if name in self.df_by_name:
            return self.df_by_name[name]
        return None