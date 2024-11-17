from property import create_prpt, PrptClass



ary = [
    create_prpt("QString", 'baseMidiRouteInput'),
    create_prpt("FilterType", 'filterType'),
]

enumClasss = [

]

classFilterMidiDestinationPrivate = PrptClass("FilterMidiDestinationPrivate", ary, enumClasss)
classFilterMidiDestinationPrivate.inhirit_from = "MidiRoutersFilter"
