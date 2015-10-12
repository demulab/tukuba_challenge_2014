
(cl:in-package :asdf)

(defsystem "fog-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "FOG" :depends-on ("_package_FOG"))
    (:file "_package_FOG" :depends-on ("_package"))
  ))