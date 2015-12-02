#ifndef BASE_TOOL_COPYABLE_H
#define BASE_TOOL_COPYABLE_H

namespace basetool
{

/// A tag class emphasises the objects are copyable.
/// The empty base class optimization applies.
/// Any derived class of copyable should be a value type.
class copyable
{
};

};

#endif  // BASE_TOOL_COPYABLE_H
