class Manager:
    def __init__(self) -> None:
        self.data = {}
    
    def add(self, *, key, value) -> bool:
        if key in self.data.keys():
            return False
        self.data[key] = value
        return True
    
    def remove(self, *, key) -> bool:
        if not key in self.data.keys():
            return False
        del self.data[key]
        return True
    
    def __setitem__(self, id, value):
        self.data[id] = value

    def __getitem__(self, id):
        return self.data[id]
    
    def __str__(self) -> str:
        return str(self.data)
    
group_manager = Manager()
card_manager = Manager()
character_manager = Manager()