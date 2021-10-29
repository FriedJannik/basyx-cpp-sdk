#pragma once

#include <basyx/base/elementcontainer.h>
#include <basyx/asset/assetinformation.h>
#include <basyx/base/token.h>

#include <basyx/serialization/base/serialization.h>

#include <basyx/submodel.h>
#include <basyx/reference.h>
#include <basyx/identifiable.h>

#include <util/optional/optional.hpp>

namespace basyx
{

using namespace basyx::base;
using namespace basyx::serialization::priv;

// ToDo: replace placeholders
using Security = int;
//using AssetInformation = int;
// --------------------------

class AssetAdministrationShell : 
	public Identifiable, 
   public ModelType<ModelTypes::AssetAdministrationShell>,
   private Identifiable::Copyable<AssetAdministrationShell>
{
private:
	util::optional<Security> security;
	util::optional<Reference> derivedFrom;
	ElementContainer<Submodel> submodels;
	AssetInformation assetInformation;
public:
	AssetAdministrationShell(util::string_view idShort, Identifier identifier, AssetInformation assetInformation)
		: Identifiable(idShort, std::move(identifier)), assetInformation(std::move(assetInformation)) {};

	AssetAdministrationShell(util::string_view idShort, util::string_view id, AssetInformation assetInformation)
		: Identifiable(idShort, Identifier(id)), assetInformation(std::move(assetInformation)) {};
public:
   AssetAdministrationShell(const AssetAdministrationShell &aas):
      Identifiable(aas.getIdShort(), std::move(aas.getIdentification())),
      assetInformation(aas.getAssetInformation()) {
      this->submodels.append(aas.getSubmodels());
   }

   AssetAdministrationShell& operator=(const AssetAdministrationShell &aas) {
      this->Identifiable::setIdentification(aas.getIdentification());
      this->getIdShort() = aas.getIdShort();
      this->submodels.append(aas.getSubmodels());
      return *this;
   }

	AssetAdministrationShell(AssetAdministrationShell &&) = default;
	AssetAdministrationShell& operator=(AssetAdministrationShell &&) = default;
public:
	const AssetInformation & getAssetInformation() const { return assetInformation; };
	void setAssetInformation(AssetInformation assetInformation) { this->assetInformation = std::move(assetInformation); };

	const util::optional<Security> & getSecurity() const { return security; };
	void setSecurity(Security security) { this->security = std::move(security); };

	const util::optional<Reference> & getDerivedFrom() const { return this->derivedFrom; };
	template<typename Ref> void setDerivedFrom(Ref && ref) { this->derivedFrom.emplace(std::forward<Ref>(ref)); };

	const ElementContainer<Submodel> & getSubmodels() const { return this->submodels; };
	ElementContainer<Submodel> & getSubmodels() { return this->submodels; };
   void setSubmodels(ElementContainer<Submodel> submodels) { this->submodels = std::move(submodels); };


   // Referable - special purpose
   void setIdShort(Token<Deserializer> t, std::string idShort) {
      this->Identifiable::setIdShort(idShort);
   }
   void setParent(Token<Deserializer> t, Referable * referable) {
      this->Identifiable::setParent(referable);
   }
   void setCategory(Token<Deserializer> t, std::string category) {
      this->Identifiable::setCategory(category);
   }
   void setDisplayname(Token<Deserializer> t, langstringset_t displayname) {
      this->Identifiable::setDisplayname(displayname);
   }
   void setDescription(Token<Deserializer> t, langstringset_t description) {
      this->Identifiable::setDescription(description);
   }

   // Identifiable - special purpose
   void setIdentification(Token<Deserializer> t, Identifier identifier) {
      this->Identifiable::setIdentification(identifier);
   }
   void setAdministration(Token<Deserializer> t,
                          AdministrativeInformation administrativeInformation) {
      this->Identifiable::setAdministration(administrativeInformation);
   }
};

};
