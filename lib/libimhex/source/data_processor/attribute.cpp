#include <hex/data_processor/attribute.hpp>

#include <hex/helpers/shared_data.hpp>

namespace hex::dp {

    Attribute::Attribute(IOType ioType, Type type, std::string unlocalizedName) : m_id(SharedData::dataProcessorAttrIdCounter++), m_ioType(ioType), m_type(type), m_unlocalizedName(std::move(unlocalizedName)) {
        this->m_allowsImmediate = ioType == Attribute::IOType::In &&
            (type == Attribute::Type::Integer || type == Attribute::Type::Float);
    }

    Attribute::~Attribute() {
        for (auto &[linkId, attr] : this->getConnectedAttributes())
            attr->removeConnectedAttribute(linkId);
    }

    void Attribute::addConnectedAttribute(u32 linkId, Attribute* to) {
        this->m_connectedAttributes.insert({ linkId, to });

        if (this->allowsImmediate()) {
            this->m_integerImmediate = 0;
            this->m_floatImmediate = 0.0f;
        }
    }
}