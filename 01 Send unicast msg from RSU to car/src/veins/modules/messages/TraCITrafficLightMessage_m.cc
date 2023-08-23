//
// Generated file, do not edit! Created by nedtool 5.7 from veins/modules/messages/TraCITrafficLightMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include "TraCITrafficLightMessage_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace {
template <class T> inline
typename std::enable_if<std::is_polymorphic<T>::value && std::is_base_of<omnetpp::cObject,T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)(static_cast<const omnetpp::cObject *>(t));
}

template <class T> inline
typename std::enable_if<std::is_polymorphic<T>::value && !std::is_base_of<omnetpp::cObject,T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)dynamic_cast<const void *>(t);
}

template <class T> inline
typename std::enable_if<!std::is_polymorphic<T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)static_cast<const void *>(t);
}

}

namespace veins {

// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule to generate operator<< for shared_ptr<T>
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const std::shared_ptr<T>& t) { return out << t.get(); }

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');

    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("veins::TrafficLightAtrributeType");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("veins::TrafficLightAtrributeType"));
    e->insert(NONE, "NONE");
    e->insert(LOGICID, "LOGICID");
    e->insert(PHASEID, "PHASEID");
    e->insert(SWITCHTIME, "SWITCHTIME");
    e->insert(STATE, "STATE");
)

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("veins::TrafficLightChangeSource");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("veins::TrafficLightChangeSource"));
    e->insert(UNKNOWN, "UNKNOWN");
    e->insert(SUMO, "SUMO");
    e->insert(LOGIC, "LOGIC");
    e->insert(RSU, "RSU");
)

Register_Class(TraCITrafficLightMessage)

TraCITrafficLightMessage::TraCITrafficLightMessage(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

TraCITrafficLightMessage::TraCITrafficLightMessage(const TraCITrafficLightMessage& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

TraCITrafficLightMessage::~TraCITrafficLightMessage()
{
}

TraCITrafficLightMessage& TraCITrafficLightMessage::operator=(const TraCITrafficLightMessage& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void TraCITrafficLightMessage::copy(const TraCITrafficLightMessage& other)
{
    this->tlId = other.tlId;
    this->changedAttribute = other.changedAttribute;
    this->oldValue = other.oldValue;
    this->newValue = other.newValue;
    this->changeSource = other.changeSource;
}

void TraCITrafficLightMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->tlId);
    doParsimPacking(b,this->changedAttribute);
    doParsimPacking(b,this->oldValue);
    doParsimPacking(b,this->newValue);
    doParsimPacking(b,this->changeSource);
}

void TraCITrafficLightMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->tlId);
    doParsimUnpacking(b,this->changedAttribute);
    doParsimUnpacking(b,this->oldValue);
    doParsimUnpacking(b,this->newValue);
    doParsimUnpacking(b,this->changeSource);
}

const char * TraCITrafficLightMessage::getTlId() const
{
    return this->tlId.c_str();
}

void TraCITrafficLightMessage::setTlId(const char * tlId)
{
    this->tlId = tlId;
}

int TraCITrafficLightMessage::getChangedAttribute() const
{
    return this->changedAttribute;
}

void TraCITrafficLightMessage::setChangedAttribute(int changedAttribute)
{
    this->changedAttribute = changedAttribute;
}

const char * TraCITrafficLightMessage::getOldValue() const
{
    return this->oldValue.c_str();
}

void TraCITrafficLightMessage::setOldValue(const char * oldValue)
{
    this->oldValue = oldValue;
}

const char * TraCITrafficLightMessage::getNewValue() const
{
    return this->newValue.c_str();
}

void TraCITrafficLightMessage::setNewValue(const char * newValue)
{
    this->newValue = newValue;
}

int TraCITrafficLightMessage::getChangeSource() const
{
    return this->changeSource;
}

void TraCITrafficLightMessage::setChangeSource(int changeSource)
{
    this->changeSource = changeSource;
}

class TraCITrafficLightMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_tlId,
        FIELD_changedAttribute,
        FIELD_oldValue,
        FIELD_newValue,
        FIELD_changeSource,
    };
  public:
    TraCITrafficLightMessageDescriptor();
    virtual ~TraCITrafficLightMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(TraCITrafficLightMessageDescriptor)

TraCITrafficLightMessageDescriptor::TraCITrafficLightMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(veins::TraCITrafficLightMessage)), "omnetpp::cMessage")
{
    propertynames = nullptr;
}

TraCITrafficLightMessageDescriptor::~TraCITrafficLightMessageDescriptor()
{
    delete[] propertynames;
}

bool TraCITrafficLightMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TraCITrafficLightMessage *>(obj)!=nullptr;
}

const char **TraCITrafficLightMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *TraCITrafficLightMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int TraCITrafficLightMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount() : 5;
}

unsigned int TraCITrafficLightMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_tlId
        FD_ISEDITABLE,    // FIELD_changedAttribute
        FD_ISEDITABLE,    // FIELD_oldValue
        FD_ISEDITABLE,    // FIELD_newValue
        FD_ISEDITABLE,    // FIELD_changeSource
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *TraCITrafficLightMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "tlId",
        "changedAttribute",
        "oldValue",
        "newValue",
        "changeSource",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int TraCITrafficLightMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 't' && strcmp(fieldName, "tlId") == 0) return base+0;
    if (fieldName[0] == 'c' && strcmp(fieldName, "changedAttribute") == 0) return base+1;
    if (fieldName[0] == 'o' && strcmp(fieldName, "oldValue") == 0) return base+2;
    if (fieldName[0] == 'n' && strcmp(fieldName, "newValue") == 0) return base+3;
    if (fieldName[0] == 'c' && strcmp(fieldName, "changeSource") == 0) return base+4;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *TraCITrafficLightMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_tlId
        "int",    // FIELD_changedAttribute
        "string",    // FIELD_oldValue
        "string",    // FIELD_newValue
        "int",    // FIELD_changeSource
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **TraCITrafficLightMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_changedAttribute: {
            static const char *names[] = { "enum", "enum",  nullptr };
            return names;
        }
        case FIELD_changeSource: {
            static const char *names[] = { "enum", "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *TraCITrafficLightMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_changedAttribute:
            if (!strcmp(propertyname, "enum")) return "TrafficLightAtrributeType";
            if (!strcmp(propertyname, "enum")) return "veins::TrafficLightAtrributeType";
            return nullptr;
        case FIELD_changeSource:
            if (!strcmp(propertyname, "enum")) return "TrafficLightChangeSource";
            if (!strcmp(propertyname, "enum")) return "veins::TrafficLightChangeSource";
            return nullptr;
        default: return nullptr;
    }
}

int TraCITrafficLightMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    TraCITrafficLightMessage *pp = (TraCITrafficLightMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *TraCITrafficLightMessageDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    TraCITrafficLightMessage *pp = (TraCITrafficLightMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TraCITrafficLightMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    TraCITrafficLightMessage *pp = (TraCITrafficLightMessage *)object; (void)pp;
    switch (field) {
        case FIELD_tlId: return oppstring2string(pp->getTlId());
        case FIELD_changedAttribute: return enum2string(pp->getChangedAttribute(), "veins::TrafficLightAtrributeType");
        case FIELD_oldValue: return oppstring2string(pp->getOldValue());
        case FIELD_newValue: return oppstring2string(pp->getNewValue());
        case FIELD_changeSource: return enum2string(pp->getChangeSource(), "veins::TrafficLightChangeSource");
        default: return "";
    }
}

bool TraCITrafficLightMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    TraCITrafficLightMessage *pp = (TraCITrafficLightMessage *)object; (void)pp;
    switch (field) {
        case FIELD_tlId: pp->setTlId((value)); return true;
        case FIELD_changedAttribute: pp->setChangedAttribute((veins::TrafficLightAtrributeType)string2enum(value, "veins::TrafficLightAtrributeType")); return true;
        case FIELD_oldValue: pp->setOldValue((value)); return true;
        case FIELD_newValue: pp->setNewValue((value)); return true;
        case FIELD_changeSource: pp->setChangeSource((veins::TrafficLightChangeSource)string2enum(value, "veins::TrafficLightChangeSource")); return true;
        default: return false;
    }
}

const char *TraCITrafficLightMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *TraCITrafficLightMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    TraCITrafficLightMessage *pp = (TraCITrafficLightMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

} // namespace veins

