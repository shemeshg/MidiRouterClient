# ver 1.0
from string import Template

def initCapital(s):
    return s[0].upper() + s[1:]

def create_prpt(type_name, name, is_writable=True, is_notify=True, is_list = False, init_val = ""):
    p = Prpt(type_name, name)
    p.is_bindable = False
    p.is_writable = is_writable
    p.is_notify = is_notify
    p.is_list = is_list
    p.init_val = init_val
    if is_list:
        p.is_writable = False        
    return p

class EnumClass:
    class_name = ""
    class_options = []

    def __init__(self, class_name, class_options):
        self.class_name = class_name
        self.class_options = class_options
       
    def public_h_file(self):
        t = Template(
"""
enum class ${class_name} {
        ${class_options}
    };
Q_ENUM(${class_name})
""")
        coma_class_options = ", ".join(self.class_options)
        return t.substitute(class_name=self.class_name, class_options=coma_class_options)
    

class Prpt:
    is_bindable=False
    is_writable = False
    is_notify = False
    is_new_in_contr = False
    field_type = ""
    field_name = ""
    field_name_initCap = ""
    writable_declare_only = False
    readable_declare_only = False
    is_getter_ref = False
    is_list = False
    init_val = ""
    
    writable_declare_only_template = Template(
"""
void set${field_name_initCap}(const ${field_type} ${ampr}new${field_name_initCap});
""")
    readable_declare_only_template = Template("""${field_type} ${ref_str}${field_name}() ${const_str};""")


    writable_template = Template(
"""
void set${field_name_initCap}(const ${field_type} ${ampr}new${field_name_initCap})
    {
        if (m_${field_name} == new${field_name_initCap})
            return;
        m_${field_name} = new${field_name_initCap};
        emit ${field_name}Changed();
    }
""")

    readable_template = Template("""${field_type} ${ref_str}${field_name}() ${const_str}{return m_${field_name};}""")
   
        
    

    def __init__(self, field_type, field_name):
        self.field_type = field_type
        self.field_name = field_name
        self.field_name_initCap = initCapital(field_name)


    def get_Q_OBJECT(self):
        bindable_template = Template("""BINDABLE bindable${field_name_initCap}""")
        bindable_txt = ""
        if self.is_bindable:
            bindable_txt = bindable_template.substitute(field_name_initCap=self.field_name_initCap)

        writable_template = Template("""WRITE set${field_name_initCap}""")
        writable_text = ""
        if self.is_writable:
            writable_text = writable_template.substitute(field_name_initCap = self.field_name_initCap)

        notify_template = Template("""NOTIFY ${field_name}Changed""")
        notify_text = "CONSTANT"
        if self.is_notify:
            notify_text = notify_template.substitute(field_name = self.field_name)

        t = Template("""Q_PROPERTY(${field_type} ${field_name} READ ${field_name} ${writable_text} ${notify_text} ${bindable_txt})
    """)

        return t.substitute(field_type=self.field_type, field_name = self.field_name , field_name_initCap=self.field_name_initCap, 
            bindable_txt=bindable_txt, writable_text=writable_text, notify_text=notify_text)
        

    def public_h_file(self):
        ampr  = "&"
        if self.field_type == "bool" or self.field_type == "int":
            ampr = ""

        bindable_template = Template("""QBindable<${field_type}> bindable${field_name_initCap}() { return &m_${field_name}; }""")
        bindable_txt = ""
        if self.is_bindable:
            bindable_txt = bindable_template.substitute(field_type=self.field_type, field_name=self.field_name,field_name_initCap=self.field_name_initCap)


        writable_text = ""
        if self.is_writable:
            writable_template = self.writable_template
            if self.writable_declare_only:
                writable_template = self.writable_declare_only_template
            writable_text = writable_template.substitute(field_type=self.field_type, field_name = self.field_name , 
                field_name_initCap=self.field_name_initCap, ampr=ampr)

        const_str = "const"
        ref_str = ""
        if self.is_getter_ref:
            ref_str = "&"
            const_str = ""

        readable_template = self.readable_template
        if self.is_list:
            readable_template = Template("""${field_type} ${ref_str}${field_name}() ${const_str}{return *m_${field_name};}""")

        if self.readable_declare_only:
            readable_template = self.readable_declare_only_template        
        readable_text = readable_template.substitute(field_type=self.field_type, field_name = self.field_name,
                const_str = const_str, ref_str = ref_str)
        t = Template(
"""
    ${bindable_txt}
    ${readable_text} 
    ${writable_text}
"""            
        )
        return t.substitute(field_type=self.field_type, field_name = self.field_name,
            writable_text=writable_text,bindable_txt=bindable_txt,
            readable_text = readable_text, const_str = const_str, ref_str = ref_str)

    def signals_h_file(self):
        if self.is_notify:
            t = Template("""void ${field_name}Changed();
    """)
            return t.substitute(field_name = self.field_name )
        else:
            return ""

    def private_h_file(self, class_name):
        if self.field_type == "int":
            self.init_val = "= 0"
        if self.field_type == "bool":
            self.init_val = "= false"
        
        if self.is_bindable:
            t = Template("""Q_OBJECT_BINDABLE_PROPERTY(${class_name}, ${field_type}, m_${field_name}, &${class_name}::${field_name}Changed)
    """)            
        else:
            t = Template("""${field_type} m_${field_name} ${init_val};
    """)    
            if self.is_list:
                t = Template("""${field_type} *m_${field_name} ${init_val};
    """)    
        return t.substitute(field_name = self.field_name,field_type=self.field_type,class_name=class_name,init_val=self.init_val )

    def destructot_h_file(self):
        type_in_list = self.field_type.split("<")[1].split(">")[0]
        t = Template("""clearList<${type_in_list}>();
    """)
        return t.substitute(type_in_list=type_in_list)    

    def public_slots_h_file(self):
        type_in_list = self.field_type.split("<")[1].split(">")[0]
        type_in_list_no_str = type_in_list.replace("*","");
        t = Template(
        """
        template<typename T = ${type_in_list}>
        std::enable_if_t<std::is_same_v<T, ${type_in_list}>, void>
        delListItem(int id){
            if (id < m_${field_name}->size())
            {
                delete m_${field_name}->at(id);
                m_${field_name}->removeAt(id);
                emit ${field_name}Changed();
            }
        }

        ${type_in_list} addListItem(${type_in_list} item)
        {
            m_${field_name}->push_back(item);
            emit ${field_name}Changed();
            return item;
        }

        template<typename T = ${type_in_list} >
        std::enable_if_t<std::is_same_v<T, ${type_in_list} >, ${type_in_list} >
        addNewListItem()
        {
            auto item = new ${type_in_list_no_str}(this);
            m_${field_name}->push_back(item);
            emit ${field_name}Changed();
            return item;
        }

        template<typename T = ${type_in_list} >
        std::enable_if_t<std::is_same_v<T, ${type_in_list} >, void>
        clearList(){
            qDeleteAll(*m_${field_name});
            m_${field_name}->clear();
            emit ${field_name}Changed();
        }

        template<typename T = ${type_in_list}>
        std::enable_if_t<std::is_same_v<T, ${type_in_list}>, const QList<${type_in_list}>>
        listItems(){
            return *m_${field_name};
        }

        """)
        return t.substitute(field_name = self.field_name,field_type=self.field_type,
                            field_name_initCap=self.field_name_initCap,type_in_list=type_in_list,
                             type_in_list_no_str = type_in_list_no_str )

class PrptClass:
    class_name = ""
    inhirit_from = "QObject"
    prptAry = []
    enumClassAry = []
    is_hpp = True
    def __init__(self, class_name, prptAry, enumClassAry, is_hpp = True):
        self.class_name = class_name
        self.prptAry = prptAry
        self.enumClassAry = enumClassAry
        self.is_hpp = is_hpp

    def getClassCpp(self):
        contr_init = [self.inhirit_from + "(parent)"]
        for row in self.prptAry:
            if row.is_new_in_contr:
                contr_template = Template("""m_${field_name}(new ${field_name_type}(this))""")
                contr_init.append(contr_template.substitute(field_name = row.field_name, field_name_type = row.field_type.split()[0]) )
        contr_init_text = ",".join(contr_init)
        t=Template(
""" 
 ${class_name}:: ${class_name}(QObject *parent)
    : ${contr_init_text}
{
    ctorClass();
}
"""
        )
        return t.substitute(class_name = self.class_name,
            contr_init_text=contr_init_text,
            inhirit_from = self.inhirit_from)

    def getClassHeader(self):
        t=Template(
"""
//-only-file header
class ${class_name} : public ${inhirit_from}
{
    Q_OBJECT
    ${q_object_content}
    QML_ELEMENT
public:
    ${constructor_h_file}
    virtual ~${class_name}() {
        ${destructor_h_file}
    }

    ${public_content}
    
    ${public_pointer_list}
    
signals:
    ${signals_content}

protected:
    ${protected_content}

private:
    ${private_content}
};
//-only-file null
"""            
        )

        return t.substitute(class_name = self.class_name, 
            q_object_content=self.get_q_object_content(), 
            public_content=self.get_public_content(),
            signals_content=self.get_signals_content(),
            private_content=self.get_private_content(),
            protected_content = self.get_protected_content(),
            public_pointer_list = self.get_public_pointer_list(),
            destructor_h_file = self.get_destructor_h_file(),
            constructor_h_file = self.get_constructor_h_file(),
            inhirit_from = self.inhirit_from)

    def get_q_object_content(self):
        q_object_content = ""
        for row in self.prptAry:
            q_object_content = q_object_content + row.get_Q_OBJECT()
        return q_object_content

    def get_public_content(self):
        public_content = ""
        for row in self.enumClassAry:
            public_content = public_content + row.public_h_file()        
        for row in self.prptAry:
            public_content = public_content + row.public_h_file()
        return public_content

    def get_signals_content(self):
        signals_content = ""
        for row in self.prptAry:
            signals_content = signals_content + row.signals_h_file()
        return signals_content

    def get_private_content(self):
        private_content = "void ctorClass(); \n"
        if self.is_hpp:
            private_content = ""
        for row in self.prptAry:
            if row.is_writable == True:
                private_content = private_content + row.private_h_file(self.class_name)
        return private_content

    def get_protected_content(self):
        private_content = ""
        for row in self.prptAry:
            if row.is_writable == False:
                private_content = private_content + row.private_h_file(self.class_name)
        return private_content
    
    def get_public_pointer_list(self):
        private_content = ""
        for row in self.prptAry:
            if row.is_list:
                private_content = private_content + row.public_slots_h_file()
        return private_content
    
    def get_destructor_h_file(self):
        private_content = ""
        for row in self.prptAry:
            if row.is_list:
                private_content = private_content + row.destructot_h_file()
        return private_content

    def get_constructor_h_file(self):        
        t = Template("    ${class_name}(QObject *parent);\n")
        
        if self.is_hpp:                      
            t = Template("""
    ${class_name}(QObject *parent):${inhirit_from}(parent){}
""")
        return t.substitute(class_name = self.class_name, inhirit_from = self.inhirit_from)

        
            

"""
ary = []
p = Prpt("QString",'message')
p.is_bindable = False
p.is_writable = True
p.is_notify = True
ary.append(p)
c = PrptClass("Msg", ary, [])
print (c.getClassHeader())
print ("#####################")
print (c.getClassCpp())
print ("#####################")


ary = []
p = Prpt("QString",'firstName')
p.is_bindable = True
p.is_writable = True
p.is_notify = True
ary.append(p)
p = Prpt("QString",'lastName')
p.is_bindable = True
p.is_writable = True
p.is_notify = True
ary.append(p)
p = Prpt("QString",'fullName')
p.is_bindable = True
p.is_writable = False
p.is_notify = True
ary.append(p)
p = Prpt("Msg *",'msg')
p.is_bindable = False
p.is_writable = False
p.is_notify = False
p.is_new_in_contr = True
ary.append(p)
p = Prpt("MyListType *",'myList')
p.is_bindable = False
p.is_writable = False
p.is_notify = False
p.is_new_in_contr = False
p.is_list = True
ary.append(p)

enumClasss = []
e = EnumClass("InfoStatus",
        ["Idile",
        "Running",
        "CaskFound",
        "FormulaFound",
        "CaskNotFound",
        "FormulaNotFound"])
enumClasss.append(e)

c = PrptClass("MyType", ary, enumClasss)
print (c.getClassHeader())
print ("#####################")
print (c.getClassCpp())

"""

