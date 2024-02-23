#include "SHSLoad.h"

shs::Load::Load(shs::settings::shs_ID_t ID, shs::LoadType ltype) 
: m_ID(ID), type(ltype) {}

void shs::Load::setID(const shs::settings::shs_ID_t ID) { m_ID = ID; }
shs::settings::shs_ID_t shs::Load::getID() const { return m_ID; }
