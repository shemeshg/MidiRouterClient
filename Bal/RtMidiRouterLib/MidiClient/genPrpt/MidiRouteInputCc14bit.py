from property import create_prpt, PrptClass


ary = [
    create_prpt("int", 'channel'),
    create_prpt("int", 'cc')
]

enumClasss = []

prptClass = PrptClass("MidiRouteInputCc14bit", ary, enumClasss)
