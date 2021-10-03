import QtQuick 2.0

Loader {
    id: root
    default property Component content
    sourceComponent: undefined

    signal beforeLoading
    signal beforeUnloading

    signal afterLoaded
    signal afterUnloaded

    function load() {
        beforeLoading()
        root.sourceComponent = content
        console.debug("Item loaded: " + content)
        afterLoaded()
    }

    function unload() {
        beforeUnloading()
        root.sourceComponent = undefined
        console.debug("Item unloaded: " + content)
        afterUnloaded()
    }
}
