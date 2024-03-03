#include "SHSLoad.h"

shs::Load::Load(shs::settings::shs_ID_t ID, shs::LoadType::LoadType ltype) 
: m_loadID(ID), type(ltype) {}

void shs::Load::setID(const shs::settings::shs_ID_t ID) { m_loadID = ID; }
shs::settings::shs_ID_t shs::Load::getID() const { return m_loadID; }
