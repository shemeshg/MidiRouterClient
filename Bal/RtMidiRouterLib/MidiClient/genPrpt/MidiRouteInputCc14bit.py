from property import create_prpt, PrptClass


ary = [
    create_prpt("int", 'channel'),
    create_prpt("int", 'cc')
]

enumClasss = []

classMidiRouteInputCc14bit = PrptClass("MidiRouteInputCc14bit", ary, enumClasss)
