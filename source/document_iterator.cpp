#include <stdio.h>

#include "document.hpp"

namespace JVJSON_NAMESPACE_NAME
{

Document::Iterator Document::Begin(bool_t includeParentEndState)
{   
    return Document::Iterator(this, includeParentEndState, true);
}

Document::Iterator Document::End(void)
{   
    return Document::Iterator(this, false, false);
}

Document::Iterator::Iterator(void)
{
    this->document = nullptr;
    this->includeParentEndState = false;
    this->elementIterators = std::deque< 
        std::pair<ElementIteratorState,Element::Iterator> >();
}

Document::Iterator::Iterator(Document* document, bool_t includeParentEndState, bool_t begin)
{
    this->document = document;
    this->includeParentEndState = includeParentEndState;
    this->elementIterators = std::deque< 
        std::pair<ElementIteratorState,Element::Iterator> >();
    if ((document != nullptr) && (begin))
    {
        if (this->document->GetRootElement().IsContainer())
        {
            this->elementIterators.push_front(
                std::pair<ElementIteratorState,Element::Iterator>(
                    PARENT_BEGIN, 
                    this->document->GetRootElement().Begin()));
        }
        else
        {
            this->elementIterators.push_front(
                std::pair<ElementIteratorState,Element::Iterator>(
                    DOCUMENT_ROOT, Element::Iterator()));
        }
    }
}

Element& Document::Iterator::GetElement(void)
{        
    if (this->document == nullptr)
    {
        return undefinedElement;
    }
    
    if (this->elementIterators.size())
    {
        ElementIteratorState state = this->elementIterators[0].first;
        
        if (state == DOCUMENT_ROOT)
        {
            return this->document->GetRootElement();
        }
        else if ((state == PARENT_BEGIN) || (state == PARENT_END))
        {
            return this->elementIterators[0].second.GetParentElement();
        }
        else
        {
            return *(this->elementIterators[0].second);            
        }
    }
    
    return this->document->GetUndefinedElement();
}

std::size_t Document::Iterator::GetDepth(void)
{        
    if (this->elementIterators.size())
    {
        ElementIteratorState state = this->elementIterators[0].first;
        
        if ((state == PARENT_BEGIN) || (state == PARENT_END))
        {
            return this->elementIterators.size() - 1;
        }
        else
        {
            return this->elementIterators.size();            
        }
    }
    
    return 0U;
}

bool_t Document::Iterator::IsParentEndState(void)
{
    if (this->elementIterators.size())
    {
        ElementIteratorState state = this->elementIterators[0].first;
        
        if (state == PARENT_END)
        {
            return true;
        }
    }
    
    return false;
}

Document::Iterator Document::Iterator::operator++(int postfix)
{
    if (this->elementIterators.size())
    {
        ElementIteratorState state = this->elementIterators[0].first;
        Element& currentElement = this->GetElement();
        
        if (state == DOCUMENT_ROOT)
        {
            this->elementIterators.pop_front();
        }
        else if (state == PARENT_BEGIN)
        {
            this->elementIterators[0].first = ELEMENT;
        }
        else
        {
            if (state == PARENT_END)
            {
                this->elementIterators.pop_front();
            }
            
            while (this->elementIterators.size())
            {
                if ((state == ELEMENT) && (currentElement.IsContainer()))
                {
                    this->elementIterators.push_front(
                        std::pair<ElementIteratorState,Element::Iterator>(
                            ELEMENT, 
                            currentElement.Begin()));                
                }
                else
                {
                    (this->elementIterators[0].second)++;
                }

                if (this->elementIterators[0].second == 
                    this->elementIterators[0].second.End())
                {
                    if (this->includeParentEndState)
                    {
                        this->elementIterators[0].first = PARENT_END;
                        break;
                    }
                    else
                    {
                        this->elementIterators.pop_front();                    
                    }
                }
                else
                {
                    break;
                }
            }
        }
    }
       
    return Document::Iterator(*this);
}

bool_t Document::Iterator::operator==(const Iterator& other)
{
    if (
        (this->document == other.document) &&
        (this->elementIterators.size() == other.elementIterators.size())
       )
    {
        if (
            (this->elementIterators.size() == 0) ||
            (
             (this->elementIterators[0].first == this->elementIterators[0].first) && 
             (this->elementIterators[0].second == this->elementIterators[0].second)
            )
           )
        {
            return true;   
        }
    }
    
    return false;
}

bool_t Document::Iterator::operator!=(const Iterator& other)
{
    return !(this->operator==(other));
}

Element& Document::Iterator::operator*(void)
{
    return this->GetElement();
}    
    
}
