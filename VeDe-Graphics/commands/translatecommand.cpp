#include "translatecommand.h"

gx::TranslateCommand::TranslateCommand(gx::Vertex translation)
    :m_translation(translation)
{
}

int gx::TranslateCommand::execute()
{
    applyTranslation(m_translation);
    return 0;
}

int gx::TranslateCommand::undo()
{
    applyTranslation(-m_translation);
    return 0;
}

void gx::TranslateCommand::applyTranslation(gx::Vertex translation)
{
    QRectF redrawRect;
    foreach(auto& obj, m_objects)
    {
        redrawRect = redrawRect.united(obj->boundingBox());

        obj->translate(translation);

        redrawRect = redrawRect.united(obj->boundingBox());
    }

    getCanvas()->redraw(redrawRect);
}
