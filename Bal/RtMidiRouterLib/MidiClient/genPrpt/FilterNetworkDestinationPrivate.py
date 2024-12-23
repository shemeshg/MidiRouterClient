from property import create_prpt, PrptClass



ary = [
    create_prpt("QString", 'baseMidiRouteInput'),
    create_prpt("QString", 'serverName'),
    create_prpt("int", 'serverPort'),
]

enumClasss = [

]

classFilterNetworkDestinationPrivate = PrptClass("FilterNetworkDestinationPrivate", ary, enumClasss)
classFilterNetworkDestinationPrivate.inhirit_from = "MidiRoutersFilter"
