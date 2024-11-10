from property import Prpt, PrptClass, EnumClass

def create_prpt(type_name, name):
    p = Prpt(type_name, name)
    p.is_bindable = False
    p.is_writable = True
    p.is_notify = True
    return p

ary = [
    create_prpt("QString", 'serverStatusText'),
    create_prpt("ServerStatus", 'serverStatus')
]

enumClasss = [
    EnumClass("ServerStatus", ["STOPPED", "STARTING", "RUNNING", "FAILED"])
]

classMidiClientConnectionPrivate = PrptClass("MidiClientConnectionPrivate", ary, enumClasss)
