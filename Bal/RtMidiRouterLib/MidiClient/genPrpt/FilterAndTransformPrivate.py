from property import create_prpt, PrptClass, EnumClass

ary = [
    create_prpt("ConditionAction", 'conditionAction'),
    create_prpt("QString", 'filterChannel'),
    create_prpt("QString", 'filterEvents'),
    create_prpt("QString", 'filterData1'),
    create_prpt("QString", 'filterData2'),
]

enumClasss = [    EnumClass("ConditionAction",
        [
            "DO_NOT_DELETE",
            "DELETE_IF_NOT_MET_CONDITION",
            "DELETE_IF_MET_CONDITION"
        ])]

classFilterAndTransformPrivate = PrptClass("FilterAndTransformPrivate", ary, enumClasss)
classFilterAndTransformPrivate.inhirit_from = "MidiRoutersFilter"
