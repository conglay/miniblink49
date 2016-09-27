// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py. DO NOT MODIFY!

#ifndef NotificationEventInit_h
#define NotificationEventInit_h

#include "modules/ModulesExport.h"
#include "modules/notifications/Notification.h"
#include "modules/serviceworkers/ExtendableEventInit.h"
#include "platform/heap/Handle.h"

namespace blink {

class MODULES_EXPORT NotificationEventInit : public ExtendableEventInit {
    ALLOW_ONLY_INLINE_ALLOCATION();
public:
    NotificationEventInit();

    bool hasNotification() const { return m_notification; }
    Notification* notification() const { return m_notification; }
    void setNotification(Notification* value) { m_notification = value; }

    DECLARE_VIRTUAL_TRACE();

private:
    Member<Notification> m_notification;

    friend class V8NotificationEventInit;
};

} // namespace blink

#endif // NotificationEventInit_h