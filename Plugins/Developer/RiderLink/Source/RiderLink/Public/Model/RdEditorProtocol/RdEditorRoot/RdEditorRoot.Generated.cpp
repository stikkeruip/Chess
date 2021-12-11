//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a RdGen v1.07.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------
#include "RdEditorRoot.Generated.h"


#include "RdEditorRoot/RdEditorRoot.Generated.h"
#include "RdEditorRoot/RdEditorRoot.Generated.h"
#include "RdEditorModel/RdEditorModel.Generated.h"

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable:4250 )
#pragma warning( disable:4307 )
#pragma warning( disable:4267 )
#pragma warning( disable:4244 )
#pragma warning( disable:4100 )
#endif

namespace JetBrains {
namespace EditorPlugin {
// companion

RdEditorRoot::RdEditorRootSerializersOwner const RdEditorRoot::serializersOwner;

void RdEditorRoot::RdEditorRootSerializersOwner::registerSerializersCore(rd::Serializers const& serializers) const
{
    RdEditorModel::serializersOwner.registry(serializers);
}

void RdEditorRoot::connect(rd::Lifetime lifetime, rd::IProtocol const * protocol)
{
    RdEditorRoot::serializersOwner.registry(protocol->get_serializers());
    
    identify(*(protocol->get_identity()), rd::RdId::Null().mix("RdEditorRoot"));
    bind(lifetime, protocol, "RdEditorRoot");
}

// constants
// initializer
void RdEditorRoot::initialize()
{
    serializationHash = -441687577021743677L;
}
// primary ctor
// secondary constructor
// default ctors and dtors
RdEditorRoot::RdEditorRoot()
{
    initialize();
}
// reader
// writer
// virtual init
void RdEditorRoot::init(rd::Lifetime lifetime) const
{
    rd::RdExtBase::init(lifetime);
}
// identify
void RdEditorRoot::identify(const rd::Identities &identities, rd::RdId const &id) const
{
    rd::RdBindableBase::identify(identities, id);
}
// getters
// intern
// equals trait
// equality operators
bool operator==(const RdEditorRoot &lhs, const RdEditorRoot &rhs) {
    return &lhs == &rhs;
}
bool operator!=(const RdEditorRoot &lhs, const RdEditorRoot &rhs){
    return !(lhs == rhs);
}
// hash code trait
// type name trait
// static type name trait
// polymorphic to string
std::string RdEditorRoot::toString() const
{
    std::string res = "RdEditorRoot\n";
    return res;
}
// external to string
std::string to_string(const RdEditorRoot & value)
{
    return value.toString();
}
}
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif

