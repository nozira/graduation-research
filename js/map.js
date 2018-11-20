var map;        //YOLP地図オブジェクト（Mapオブジェクト）
var blankmap;   //白地図レイヤー
/**
 * window.onloadイベントにて地図の読込処理を行います。
 */
window.onload = function() {
    map = new Y.Map("map",{"configure":{"scrollWheelZoom":true}});
    map.addControl(new Y.LayerSetControl());
    map.addControl(new Y.SliderZoomControlHorizontal());

    //白地図レイヤーを作成します。
    blankmap = new Y.BlankMapLayer();
    setStyle();
    //レイヤーセットを作成します。
    var layerset = new Y.LayerSet("白地図", [blankmap],{"maxZoom":13, "minZoom":8});
    //Mapオブジェクトにレイヤーセットを追加します。
    map.addLayerSet("blankmap", layerset);
    //地図を描画します。
    map.drawMap(new Y.LatLng(35.6821141786951,139.75630702905684), 11, Y.LayerSetId.NORMAL);
    //表示を白地図にします。
    map.setLayerSet( "blankmap" );
}
/**
 * スタイルを設定します。
 */
function setStyle() {
    var style = {
        "area" : {
            "default" : "dcdcdc"
        },
        "label" : {
            "default" : "696969"
        },
        "border" : {
            "default" : "aaa"
        },
        "bg" : "b0c4de"
    };
    //スタイルを設定します。
    style.area["13101"]="bbbcde";
    style.area["13102"]="bbbcde";
    style.area["13103"]="bbbcde";
    style.area["13104"]="bbbcde";
    style.area["13105"]="bbbcde";
    style.area["13106"]="bbbcde";
    style.area["13107"]="bbbcde";
    style.area["13108"]="bbbcde";
    style.area["13109"]="bbbcde";
    style.area["13110"]="bbbcde";
    style.area["13111"]="ffa500";
    style.area["13112"]="ffa500";
    style.area["13113"]="ffa500";
    style.area["13114"]="ffa500";
    style.area["13115"]="ffa500";
    style.area["13116"]="ffa500";
    blankmap.setStyle(style, true);
}