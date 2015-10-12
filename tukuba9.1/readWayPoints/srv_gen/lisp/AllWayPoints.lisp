; Auto-generated. Do not edit!


(cl:in-package readWayPoints-srv)


;//! \htmlinclude AllWayPoints-request.msg.html

(cl:defclass <AllWayPoints-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass AllWayPoints-request (<AllWayPoints-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <AllWayPoints-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'AllWayPoints-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name readWayPoints-srv:<AllWayPoints-request> is deprecated: use readWayPoints-srv:AllWayPoints-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <AllWayPoints-request>) ostream)
  "Serializes a message object of type '<AllWayPoints-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <AllWayPoints-request>) istream)
  "Deserializes a message object of type '<AllWayPoints-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<AllWayPoints-request>)))
  "Returns string type for a service object of type '<AllWayPoints-request>"
  "readWayPoints/AllWayPointsRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'AllWayPoints-request)))
  "Returns string type for a service object of type 'AllWayPoints-request"
  "readWayPoints/AllWayPointsRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<AllWayPoints-request>)))
  "Returns md5sum for a message object of type '<AllWayPoints-request>"
  "b79019e7b9c24c2da4cedca4ef33b347")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'AllWayPoints-request)))
  "Returns md5sum for a message object of type 'AllWayPoints-request"
  "b79019e7b9c24c2da4cedca4ef33b347")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<AllWayPoints-request>)))
  "Returns full string definition for message of type '<AllWayPoints-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'AllWayPoints-request)))
  "Returns full string definition for message of type 'AllWayPoints-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <AllWayPoints-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <AllWayPoints-request>))
  "Converts a ROS message object to a list"
  (cl:list 'AllWayPoints-request
))
;//! \htmlinclude AllWayPoints-response.msg.html

(cl:defclass <AllWayPoints-response> (roslisp-msg-protocol:ros-message)
  ((waypoints
    :reader waypoints
    :initarg :waypoints
    :type (cl:vector geometry_msgs-msg:Pose)
   :initform (cl:make-array 0 :element-type 'geometry_msgs-msg:Pose :initial-element (cl:make-instance 'geometry_msgs-msg:Pose))))
)

(cl:defclass AllWayPoints-response (<AllWayPoints-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <AllWayPoints-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'AllWayPoints-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name readWayPoints-srv:<AllWayPoints-response> is deprecated: use readWayPoints-srv:AllWayPoints-response instead.")))

(cl:ensure-generic-function 'waypoints-val :lambda-list '(m))
(cl:defmethod waypoints-val ((m <AllWayPoints-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader readWayPoints-srv:waypoints-val is deprecated.  Use readWayPoints-srv:waypoints instead.")
  (waypoints m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <AllWayPoints-response>) ostream)
  "Serializes a message object of type '<AllWayPoints-response>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'waypoints))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'waypoints))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <AllWayPoints-response>) istream)
  "Deserializes a message object of type '<AllWayPoints-response>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'waypoints) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'waypoints)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'geometry_msgs-msg:Pose))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<AllWayPoints-response>)))
  "Returns string type for a service object of type '<AllWayPoints-response>"
  "readWayPoints/AllWayPointsResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'AllWayPoints-response)))
  "Returns string type for a service object of type 'AllWayPoints-response"
  "readWayPoints/AllWayPointsResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<AllWayPoints-response>)))
  "Returns md5sum for a message object of type '<AllWayPoints-response>"
  "b79019e7b9c24c2da4cedca4ef33b347")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'AllWayPoints-response)))
  "Returns md5sum for a message object of type 'AllWayPoints-response"
  "b79019e7b9c24c2da4cedca4ef33b347")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<AllWayPoints-response>)))
  "Returns full string definition for message of type '<AllWayPoints-response>"
  (cl:format cl:nil "geometry_msgs/Pose[] waypoints~%~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of postion and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'AllWayPoints-response)))
  "Returns full string definition for message of type 'AllWayPoints-response"
  (cl:format cl:nil "geometry_msgs/Pose[] waypoints~%~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of postion and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <AllWayPoints-response>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'waypoints) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <AllWayPoints-response>))
  "Converts a ROS message object to a list"
  (cl:list 'AllWayPoints-response
    (cl:cons ':waypoints (waypoints msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'AllWayPoints)))
  'AllWayPoints-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'AllWayPoints)))
  'AllWayPoints-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'AllWayPoints)))
  "Returns string type for a service object of type '<AllWayPoints>"
  "readWayPoints/AllWayPoints")