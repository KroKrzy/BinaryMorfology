# TODO: adapt "org.kde.plasma" here & elsewhere if needed (see README)
add_definitions(-DTRANSLATION_DOMAIN=\"plasma_applet_org.kde.plasma.binarymorfology\")

set(binarymorfology_SRCS
    binarymorfology.cpp
)

add_library(plasma_applet_binarymorfology MODULE ${binarymorfology_SRCS})

kcoreaddons_desktop_to_json(plasma_applet_binarymorfology package/metadata.desktop SERVICE_TYPES plasma-applet.desktop)

target_link_libraries(plasma_applet_binarymorfology
                      Qt5::Gui
                      KF5::Plasma
                      KF5::I18n)


install(TARGETS plasma_applet_binarymorfology DESTINATION ${KDE_INSTALL_PLUGINDIR}/plasma/applets)

plasma_install_package(package org.kde.plasma.binarymorfology)
