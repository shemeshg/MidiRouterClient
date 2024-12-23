from property import create_prpt, PrptClass



ary = [
    create_prpt("QString", 'baseMidiRouteInput'),
]

enumClasss = [

]

prptClass = PrptClass("FilterMidiDestinationPrivate", ary, enumClasss)
prptClass.inhirit_from = "MidiRoutersFilter"
