#include "./forms.h"
const std::unordered_map<std::string, SpecialFormType*> SPECIAL_FORMS{
    {"define", defineForm},{"'",quoteForm}
};