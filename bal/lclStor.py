from string import Template

class LclStor:

    prptAry = []

    def __init__(self, prptAry):
        self.prptAry = prptAry
        
    def row_is_ls(self, row):
        return hasattr(row, "is_local_storage") and row.is_local_storage
    
    def getLclStorCpp(self):
        s = ""
        t = Template("""
void BalData::load${field_name_initCap}()
{
    int s = settings.value("${field_name}", ${local_storage_default}).${to_type}();
    set${field_name_initCap}(s);
}

void BalData::save${field_name_initCap}(const ${field_type} s)
{
    settings.setValue("${field_name}", s);
    load${field_name_initCap}();
}""")
        for row in self.prptAry:
            if self.row_is_ls(row):
                to_type = "toInt"
                s = s + t.substitute(field_name=row.field_name, 
                                    field_name_initCap=row.field_name_initCap,
                                    to_type = to_type,
                                    field_type = row.field_type,
                                    local_storage_default = row.local_storage_default)
        return s   

    def getLclStorHdrPrv(self):
        s = ""
        t = Template("""
void load${field_name_initCap}();""")
        for row in self.prptAry:
            if self.row_is_ls(row):
                s = s + t.substitute(field_name_initCap=row.field_name_initCap)
        return s   
    
    def getLclStorHdrPub(self):
        s = ""
        t = Template("""
void save${field_name_initCap}(const ${field_type} ${field_name_initCap});""")
        for row in self.prptAry:
            if self.row_is_ls(row):
                s = s + t.substitute(field_name_initCap=row.field_name_initCap, 
                                     field_type = row.field_type)
        return s   
        
    def getLclStorCntr(self):
        s = ""
        t = Template("""
load${field_name_initCap}();""")
        for row in self.prptAry:
            if self.row_is_ls(row):
                s = s + t.substitute(field_name_initCap=row.field_name_initCap)
        return s   
    
# ls = LclStor(ary)    
# print( ls.getLclStorCntr())
# print( ls.getLclStorHdrPub())