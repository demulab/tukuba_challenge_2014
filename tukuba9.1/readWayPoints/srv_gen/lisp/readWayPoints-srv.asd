
(cl:in-package :asdf)

(defsystem "readWayPoints-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
)
  :components ((:file "_package")
    (:file "AllWayPoints" :depends-on ("_package_AllWayPoints"))
    (:file "_package_AllWayPoints" :depends-on ("_package"))
  ))