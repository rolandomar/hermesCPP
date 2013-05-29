/* 
 * File:   StatToken.cpp
 * Author: rmartins
 * 
 * Created on April 30, 2013, 12:07 AM
 */

#include "StatToken.h"

StatToken::StatToken() {
}

StatToken::StatToken(const StatToken& orig):
m_duration(orig.m_duration),m_i(orig.m_i)
{
}

StatToken::~StatToken() {
}

