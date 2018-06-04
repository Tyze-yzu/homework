// MemberDetails class definition
#ifndef MEMBER_DETAILS_H
#define MEMBER_DETAILS_H

#include "MemberDatabase.h" // MemberDatabase class definition

class MemberDetails
{
public:
   MemberDetails( MemberDatabase &theMemberDatabase );

   void execute( vector< Member >::iterator it );

private:
   MemberDatabase &memberDatabase; // reference to memberDatabase
}; // end class MemberDetails

#endif // MEMBER_DETAILS_H