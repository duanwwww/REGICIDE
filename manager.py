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
    
group_manager = Manager()
card_manager = Manager()
character_manager = Manager()