; Auto-generated. Do not edit!


(cl:in-package fog-srv)


;//! \htmlinclude FOG-request.msg.html

(cl:defclass <FOG-request> (roslisp-msg-protocol:ros-message)
  ((order
    :reader order
    :initarg :order
    :type cl:integer
    :initform 0))
)

(cl:defclass FOG-request (<FOG-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <FOG-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'FOG-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name fog-srv:<FOG-request> is deprecated: use fog-srv:FOG-request instead.")))

(cl:ensure-generic-function 'order-val :lambda-list '(m))
(cl:defmethod order-val ((m <FOG-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader fog-srv:order-val is deprecated.  Use fog-srv:order instead.")
  (order m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <FOG-request>) ostream)
  "Serializes a message object of type '<FOG-request>"
  (cl:let* ((signed (cl:slot-value msg 'order)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <FOG-request>) istream)
  "Deserializes a message object of type '<FOG-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'order) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<FOG-request>)))
  "Returns string type for a service object of type '<FOG-request>"
  "fog/FOGRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FOG-request)))
  "Returns string type for a service object of type 'FOG-request"
  "fog/FOGRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<FOG-request>)))
  "Returns md5sum for a message object of type '<FOG-request>"
  "2e715789d036161918201e028e4b49b7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'FOG-request)))
  "Returns md5sum for a message object of type 'FOG-request"
  "2e715789d036161918201e028e4b49b7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<FOG-request>)))
  "Returns full string definition for message of type '<FOG-request>"
  (cl:format cl:nil "int32 order~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'FOG-request)))
  "Returns full string definition for message of type 'FOG-request"
  (cl:format cl:nil "int32 order~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <FOG-request>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <FOG-request>))
  "Converts a ROS message object to a list"
  (cl:list 'FOG-request
    (cl:cons ':order (order msg))
))
;//! \htmlinclude FOG-response.msg.html

(cl:defclass <FOG-response> (roslisp-msg-protocol:ros-message)
  ((response_header
    :reader response_header
    :initarg :response_header
    :type cl:integer
    :initform 0)
   (theta
    :reader theta
    :initarg :theta
    :type cl:float
    :initform 0.0))
)

(cl:defclass FOG-response (<FOG-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <FOG-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'FOG-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name fog-srv:<FOG-response> is deprecated: use fog-srv:FOG-response instead.")))

(cl:ensure-generic-function 'response_header-val :lambda-list '(m))
(cl:defmethod response_header-val ((m <FOG-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader fog-srv:response_header-val is deprecated.  Use fog-srv:response_header instead.")
  (response_header m))

(cl:ensure-generic-function 'theta-val :lambda-list '(m))
(cl:defmethod theta-val ((m <FOG-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader fog-srv:theta-val is deprecated.  Use fog-srv:theta instead.")
  (theta m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <FOG-response>) ostream)
  "Serializes a message object of type '<FOG-response>"
  (cl:let* ((signed (cl:slot-value msg 'response_header)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'theta))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <FOG-response>) istream)
  "Deserializes a message object of type '<FOG-response>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'response_header) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'theta) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<FOG-response>)))
  "Returns string type for a service object of type '<FOG-response>"
  "fog/FOGResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FOG-response)))
  "Returns string type for a service object of type 'FOG-response"
  "fog/FOGResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<FOG-response>)))
  "Returns md5sum for a message object of type '<FOG-response>"
  "2e715789d036161918201e028e4b49b7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'FOG-response)))
  "Returns md5sum for a message object of type 'FOG-response"
  "2e715789d036161918201e028e4b49b7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<FOG-response>)))
  "Returns full string definition for message of type '<FOG-response>"
  (cl:format cl:nil "int32 response_header~%float64 theta~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'FOG-response)))
  "Returns full string definition for message of type 'FOG-response"
  (cl:format cl:nil "int32 response_header~%float64 theta~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <FOG-response>))
  (cl:+ 0
     4
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <FOG-response>))
  "Converts a ROS message object to a list"
  (cl:list 'FOG-response
    (cl:cons ':response_header (response_header msg))
    (cl:cons ':theta (theta msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'FOG)))
  'FOG-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'FOG)))
  'FOG-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FOG)))
  "Returns string type for a service object of type '<FOG>"
  "fog/FOG")