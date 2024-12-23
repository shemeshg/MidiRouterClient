from property import create_prpt, PrptClass



ary = [
    create_prpt("QString", 'baseMidiRouteInput'),
    create_prpt("QString", 'serverName'),
    create_prpt("int", 'serverPort'),
]

enumClasss = [

]

prptClass = PrptClass("FilterNetworkDestinationPrivate", ary, enumClasss)
prptClass.inhirit_from = "MidiRoutersFilter"
