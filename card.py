import suit

class Card():
    def __init__(self, *, rank: int, card_ID: int, suit: Suit, type: str):
        self.rank = rank
        self.card_ID = card_ID
        self.suit = suit
        self.type = type
        self.sticker = None
    
    def add_sticker(self, sticker: Sticker):
        self.sticker = sticker
        
    
