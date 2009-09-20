project( kastengui )

add_definitions( -DKDE_DEFAULT_DEBUG_AREA=1804 )

include_directories(
  ../core
  ../core/document
  ../core/io
  ../core/system
  view
  io
  system
  shell
  controller
)


set( kastengui_view_SRCS
  view/abstractview.cpp
  view/abstractselectionview.cpp
  view/abstracttoolinlineview.cpp
  view/abstracttoolview.cpp
)
set( kastengui_view_HDRS
  view/abstractviewfactory.h
  view/selecteddatawriteable.h
  view/abstracttoolinlineview.h
  view/abstractview.h
  view/abstractselectionview.h
  view/abstracttoolview.h
  view/dataselectable.h
  view/zoomable.h
)

set( kastengui_io_configeditor_SRCS
  io/filesystem/modelencoderfilesystemexporterconfigeditorfactory.cpp
  io/filesystem/modelencoderfilesystemexporterconfigeditor.cpp
  io/abstractmodelstreamencoderconfigeditor.cpp
  io/abstractmodelexporterconfigeditor.cpp
)
set( kastengui_io_SRCS
  ${kastengui_io_configeditor_SRCS}
)
set( kastengui_io_HDRS
  io/filesystem/modelencoderfilesystemexporterconfigeditor.h
  io/filesystem/modelencoderfilesystemexporterconfigeditorfactory.h
  io/abstractmodelstreamencoderconfigeditor.h
  io/abstractmodelexporterconfigeditor.h
  io/abstractmodelexporterconfigeditorfactory.h
  io/abstractmodelstreamencoderconfigeditorfactory.h
)


set( kastengui_system_SRCS
  system/dummyview.cpp
  system/modelcodecviewmanager.cpp
  system/viewmanager.cpp
)
set( kastengui_system_HDRS
  system/dummyview.h
  system/modelcodecviewmanager.h
  system/viewmanager.h
)

set( kastengui_shell_SRCS
  shell/viewbox.cpp
  shell/toolinlineviewwidget.cpp
  shell/toolviewdockwidget.cpp
  shell/abstractviewarea.cpp
  shell/abstractgroupedviews.cpp
  shell/viewareabox.cpp
  shell/tabbedviews.cpp
  shell/multiviewareas.cpp
  shell/shellwindow.cpp
  shell/statusbar.cpp
  shell/statusbarlayout.cpp
)
set( kastengui_shell_HDRS
  shell/shellwindow.h
  shell/abstractviewarea.h
  shell/abstractgroupedviews.h
  shell/statusbar.h
  shell/viewareabox.h
  shell/viewbox.h
  shell/tabbedviews.h
  shell/multiviewareas.h
  shell/toolinlineviewwidget.h
  shell/toolviewdockwidget.h
  shell/statusbarlayout.h
  shell/toolinlineviewable.h
  shell/widgetsdockable.h
  shell/viewareasplitable.h
)

set( kastengui_controller_widgets_SRCS
  controller/togglebutton_p.cpp
  controller/togglebutton.cpp
  controller/abstractlinepopup_p.cpp
  controller/abstractlinepopup.cpp
  controller/abstracttoolwidget_p.cpp
  controller/abstracttoolwidget.cpp
)
set( kastengui_controller_SRCS
  ${kastengui_controller_widgets_SRCS}
  controller/abstractxmlguicontroller.cpp
)
set( kastengui_controller_HDRS
  controller/abstractxmlguicontroller.h
  controller/abstractlinepopup.h
  controller/togglebutton.h
  controller/abstracttoolwidget.h
)

set( kastengui_LIB_SRCS
  ${kastengui_view_SRCS}
  ${kastengui_io_SRCS}
  ${kastengui_system_SRCS}
  ${kastengui_shell_SRCS}
  ${kastengui_controller_SRCS}
)

set( kastengui_LIB_HDRS
  kastengui_export.h
  ${kastengui_view_HDRS}
  ${kastengui_io_HDRS}
  ${kastengui_system_HDRS}
  ${kastengui_shell_HDRS}
  ${kastengui_controller_HDRS}
)


kde4_add_library( kastengui SHARED ${kastengui_LIB_SRCS} )
target_link_libraries( kastengui
  kastencore
  ${KDE4_KDEUI_LIBS}
)
set_target_properties( kastengui  PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION} )

install( TARGETS kastengui  ${INSTALL_TARGETS_DEFAULT_ARGS} )

install( FILES ${kastengui_LIB_HDRS}  DESTINATION  ${INCLUDE_INSTALL_DIR}/kasten  COMPONENT Devel )