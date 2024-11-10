from property import Prpt, PrptClass

def create_prpt(type_name, name):
    p = Prpt(type_name, name)
    p.is_bindable = False
    p.is_writable = True
    p.is_notify = True
    return p

ary = [
    create_prpt("QString", 'name')
]

enumClasss = []

classMidiRouteInputPrivate = PrptClass("MidiRouteInputPrivate", ary, enumClasss)
