<GameProjectFile>
  <PropertyGroup Type="Scene" Name="main_scene" ID="c1e812d7-a479-48a0-9512-b164aaad93b9" Version="2.2.9.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="30" Speed="1.0000">
        <Timeline ActionTag="-1647960636" Property="Position">
          <PointFrame FrameIndex="0" X="1700.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="30" X="1136.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-169630990" Property="Position">
          <PointFrame FrameIndex="0" X="-324.0000" Y="290.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="30" X="300.0000" Y="290.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="fadein" StartIndex="0" EndIndex="30">
          <RenderColor A="255" R="205" G="92" B="92" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Scene" Tag="19" ctype="GameNodeObjectData">
        <Size X="1136.0000" Y="640.0000" />
        <Children>
          <AbstractNodeData Name="Sprite_bg" ActionTag="879935419" Tag="20" IconVisible="False" LeftMargin="0.5124" RightMargin="-0.5125" ctype="SpriteObjectData">
            <Size X="1136.0000" Y="640.0000" />
            <AnchorPoint />
            <Position X="0.5124" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0005" />
            <PreSize />
            <FileData Type="Normal" Path="images/ui/beijing01.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="Image_12" ActionTag="1111814305" Tag="116" IconVisible="False" TopMargin="556.0000" Scale9Enable="True" TopEage="7" BottomEage="7" Scale9OriginY="7" Scale9Width="1136" Scale9Height="2" ctype="ImageViewObjectData">
            <Size X="1136.0000" Y="84.0000" />
            <Children>
              <AbstractNodeData Name="btn_back" ActionTag="-435637376" Tag="63" IconVisible="False" LeftMargin="17.5000" RightMargin="1043.5000" TopMargin="4.0000" BottomMargin="20.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="45" Scale9Height="38" OutlineSize="1" ShadowOffsetX="2" ShadowOffsetY="-2" ctype="ButtonObjectData">
                <Size X="75.0000" Y="60.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="55.0000" Y="50.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.0484" Y="0.5952" />
                <PreSize X="0.0660" Y="0.0938" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Normal" Path="images/button/button_57.png" Plist="" />
                <PressedFileData Type="Normal" Path="images/button/button_57.png" Plist="" />
                <NormalFileData Type="Normal" Path="images/button/button_56.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="Image_2" ActionTag="1064438741" Tag="64" IconVisible="False" LeftMargin="107.5000" RightMargin="603.5000" TopMargin="22.0000" BottomMargin="22.0000" Scale9Enable="True" LeftEage="20" RightEage="20" Scale9OriginX="20" Scale9Width="2" Scale9Height="40" ctype="ImageViewObjectData">
                <Size X="425.0000" Y="40.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="320.0000" Y="42.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.2817" Y="0.5000" />
                <PreSize X="0.3741" Y="0.0625" />
                <FileData Type="Normal" Path="images/ui/ui_152.png" Plist="" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="1.0000" Y="0.1312" />
            <FileData Type="Normal" Path="images/ui/ui_138.png" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="Sprite_saber" ActionTag="-1647960636" Tag="46" IconVisible="False" LeftMargin="1136.0000" RightMargin="-564.0000" TopMargin="33.0000" ctype="SpriteObjectData">
            <Size X="564.0000" Y="607.0000" />
            <AnchorPoint ScaleX="1.0000" />
            <Position X="1700.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="1.4965" />
            <PreSize />
            <FileData Type="Normal" Path="images/ui/ui_139.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="Node_panel" ActionTag="-169630990" Tag="117" IconVisible="True" LeftMargin="-324.0000" RightMargin="1460.0000" TopMargin="350.0000" BottomMargin="290.0000" ctype="SingleNodeObjectData">
            <Size />
            <Children>
              <AbstractNodeData Name="sp_circle" ActionTag="1804806451" Tag="190" IconVisible="False" LeftMargin="-179.0000" RightMargin="-179.0000" TopMargin="-179.0000" BottomMargin="-179.0000" ctype="SpriteObjectData">
                <Size X="358.0000" Y="358.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize />
                <FileData Type="Normal" Path="images/ui/ui_227.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="Node_gear" ActionTag="-2112802737" Tag="188" Rotation="360.0000" RotationSkewX="360.0000" RotationSkewY="360.0000" IconVisible="True" ctype="SingleNodeObjectData">
                <Size />
                <Children>
                  <AbstractNodeData Name="sp_gear_tl" ActionTag="-935780029" Tag="191" IconVisible="False" LeftMargin="-152.0000" TopMargin="-152.0000" ctype="SpriteObjectData">
                    <Size X="152.0000" Y="152.0000" />
                    <AnchorPoint ScaleX="1.0000" />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize />
                    <FileData Type="Normal" Path="images/ui/ui_135.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="sp_gear_tr" ActionTag="-54915394" Tag="192" IconVisible="False" RightMargin="-152.0000" TopMargin="-152.0000" FlipX="True" ctype="SpriteObjectData">
                    <Size X="152.0000" Y="152.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize />
                    <FileData Type="Normal" Path="images/ui/ui_135.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="sp_gear_bl" ActionTag="-560331152" Tag="193" IconVisible="False" LeftMargin="-152.0000" BottomMargin="-152.0000" FlipY="True" ctype="SpriteObjectData">
                    <Size X="152.0000" Y="152.0000" />
                    <AnchorPoint ScaleX="1.0000" ScaleY="1.0000" />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize />
                    <FileData Type="Normal" Path="images/ui/ui_135.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="sp_gear_br" ActionTag="-1914237110" Tag="194" IconVisible="False" RightMargin="-152.0000" BottomMargin="-152.0000" FlipX="True" FlipY="True" ctype="SpriteObjectData">
                    <Size X="152.0000" Y="152.0000" />
                    <AnchorPoint ScaleY="1.0000" />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize />
                    <FileData Type="Normal" Path="images/ui/ui_135.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize />
              </AbstractNodeData>
              <AbstractNodeData Name="sp_map" ActionTag="1766080141" Tag="21" IconVisible="False" LeftMargin="-64.5000" RightMargin="-64.5000" TopMargin="-64.5000" BottomMargin="-64.5000" ctype="SpriteObjectData">
                <Size X="129.0000" Y="129.0000" />
                <Children>
                  <AbstractNodeData Name="btn_map" ActionTag="145807733" Tag="40" IconVisible="False" LeftMargin="16.5000" RightMargin="16.5000" TopMargin="16.5000" BottomMargin="16.5000" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="66" Scale9Height="74" OutlineSize="1" ShadowOffsetX="2" ShadowOffsetY="-2" ctype="ButtonObjectData">
                    <Size X="96.0000" Y="96.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="64.5000" Y="64.5000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="0.7442" Y="0.7442" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Normal" Path="images/button/button_55.png" Plist="" />
                    <PressedFileData Type="Normal" Path="images/button/button_55.png" Plist="" />
                    <NormalFileData Type="Normal" Path="images/button/button_54.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position />
                <Scale ScaleX="1.2000" ScaleY="1.2000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize />
                <FileData Type="Normal" Path="images/ui/ui_136.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="sp_bag" ActionTag="441041025" Tag="22" IconVisible="False" LeftMargin="-64.5000" RightMargin="-64.5000" TopMargin="-214.5000" BottomMargin="85.5000" ctype="SpriteObjectData">
                <Size X="129.0000" Y="129.0000" />
                <Children>
                  <AbstractNodeData Name="btn_bag" ActionTag="956342936" Tag="41" IconVisible="False" LeftMargin="16.5000" RightMargin="16.5000" TopMargin="16.5000" BottomMargin="16.5000" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="66" Scale9Height="74" OutlineSize="1" ShadowOffsetX="2" ShadowOffsetY="-2" ctype="ButtonObjectData">
                    <Size X="96.0000" Y="96.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="64.5000" Y="64.5000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="0.7442" Y="0.7442" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Normal" Path="images/button/button_19.png" Plist="" />
                    <PressedFileData Type="Normal" Path="images/button/button_19.png" Plist="" />
                    <NormalFileData Type="Normal" Path="images/button/button_18.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position Y="150.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize />
                <FileData Type="Normal" Path="images/ui/ui_136.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="sp_skill" ActionTag="-2037133338" Tag="23" IconVisible="False" LeftMargin="-194.5000" RightMargin="65.5000" TopMargin="-139.5000" BottomMargin="10.5000" ctype="SpriteObjectData">
                <Size X="129.0000" Y="129.0000" />
                <Children>
                  <AbstractNodeData Name="btn_skill" ActionTag="1944354887" Tag="42" IconVisible="False" LeftMargin="16.5000" RightMargin="16.5000" TopMargin="16.5000" BottomMargin="16.5000" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="66" Scale9Height="74" OutlineSize="1" ShadowOffsetX="2" ShadowOffsetY="-2" ctype="ButtonObjectData">
                    <Size X="96.0000" Y="96.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="64.5000" Y="64.5000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="0.7442" Y="0.7442" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Normal" Path="images/button/button_23.png" Plist="" />
                    <PressedFileData Type="Normal" Path="images/button/button_23.png" Plist="" />
                    <NormalFileData Type="Normal" Path="images/button/button_22.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="-130.0000" Y="75.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize />
                <FileData Type="Normal" Path="images/ui/ui_136.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="sp_endless" ActionTag="328338115" Tag="24" IconVisible="False" LeftMargin="65.5000" RightMargin="-194.5000" TopMargin="10.5000" BottomMargin="-139.5000" ctype="SpriteObjectData">
                <Size X="129.0000" Y="129.0000" />
                <Children>
                  <AbstractNodeData Name="btn_map_endless" ActionTag="-1197802871" Tag="43" IconVisible="False" LeftMargin="16.5000" RightMargin="16.5000" TopMargin="16.5000" BottomMargin="16.5000" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="66" Scale9Height="74" OutlineSize="1" ShadowOffsetX="2" ShadowOffsetY="-2" ctype="ButtonObjectData">
                    <Size X="96.0000" Y="96.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="64.5000" Y="64.5000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="0.7442" Y="0.7442" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Normal" Path="images/button/button_53.png" Plist="" />
                    <PressedFileData Type="Normal" Path="images/button/button_53.png" Plist="" />
                    <NormalFileData Type="Normal" Path="images/button/button_52.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="130.0000" Y="-75.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize />
                <FileData Type="Normal" Path="images/ui/ui_136.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="sp_equip" ActionTag="1224719053" Tag="25" IconVisible="False" LeftMargin="-194.5000" RightMargin="65.5000" TopMargin="10.5000" BottomMargin="-139.5000" ctype="SpriteObjectData">
                <Size X="129.0000" Y="129.0000" />
                <Children>
                  <AbstractNodeData Name="btn_equip" ActionTag="-115442503" Tag="44" IconVisible="False" LeftMargin="16.5000" RightMargin="16.5000" TopMargin="16.5000" BottomMargin="16.5000" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="66" Scale9Height="74" OutlineSize="1" ShadowOffsetX="2" ShadowOffsetY="-2" ctype="ButtonObjectData">
                    <Size X="96.0000" Y="96.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="64.5000" Y="64.5000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="0.7442" Y="0.7442" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Normal" Path="images/button/button_21.png" Plist="" />
                    <PressedFileData Type="Normal" Path="images/button/button_21.png" Plist="" />
                    <NormalFileData Type="Normal" Path="images/button/button_20.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="-130.0000" Y="-75.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize />
                <FileData Type="Normal" Path="images/ui/ui_136.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="sp_shop" ActionTag="1714631763" Tag="26" IconVisible="False" LeftMargin="-64.5000" RightMargin="-64.5000" TopMargin="85.5000" BottomMargin="-214.5000" ctype="SpriteObjectData">
                <Size X="129.0000" Y="129.0000" />
                <Children>
                  <AbstractNodeData Name="btn_shop" ActionTag="621887940" Tag="45" IconVisible="False" LeftMargin="16.5000" RightMargin="16.5000" TopMargin="16.5000" BottomMargin="16.5000" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="66" Scale9Height="74" OutlineSize="1" ShadowOffsetX="2" ShadowOffsetY="-2" ctype="ButtonObjectData">
                    <Size X="96.0000" Y="96.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="64.5000" Y="64.5000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="0.7442" Y="0.7442" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Normal" Path="images/button/button_25.png" Plist="" />
                    <PressedFileData Type="Normal" Path="images/button/button_25.png" Plist="" />
                    <NormalFileData Type="Normal" Path="images/button/button_24.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position Y="-150.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize />
                <FileData Type="Normal" Path="images/ui/ui_136.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="sp_mission" ActionTag="749608169" Tag="89" IconVisible="False" LeftMargin="65.5000" RightMargin="-194.5000" TopMargin="-139.5000" BottomMargin="10.5000" ctype="SpriteObjectData">
                <Size X="129.0000" Y="129.0000" />
                <Children>
                  <AbstractNodeData Name="btn_mission" ActionTag="-1913881469" Tag="90" IconVisible="False" LeftMargin="16.5000" RightMargin="16.5000" TopMargin="16.5000" BottomMargin="16.5000" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="66" Scale9Height="74" OutlineSize="1" ShadowOffsetX="2" ShadowOffsetY="-2" ctype="ButtonObjectData">
                    <Size X="96.0000" Y="96.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="64.5000" Y="64.5000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="0.7442" Y="0.7442" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Normal" Path="images/button/button_100.png" Plist="" />
                    <PressedFileData Type="Normal" Path="images/button/button_100.png" Plist="" />
                    <NormalFileData Type="Normal" Path="images/button/button_99.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="130.0000" Y="75.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize />
                <FileData Type="Normal" Path="images/ui/ui_136.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position X="-324.0000" Y="290.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="-0.2852" Y="0.4531" />
            <PreSize />
          </AbstractNodeData>
          <AbstractNodeData Name="Image_1" ActionTag="1454191308" Tag="62" IconVisible="False" BottomMargin="570.0000" Scale9Enable="True" LeftEage="220" RightEage="220" Scale9OriginX="220" Scale9Width="10" Scale9Height="70" ctype="ImageViewObjectData">
            <Size X="1136.0000" Y="70.0000" />
            <Children>
              <AbstractNodeData Name="ProjectNode_1" ActionTag="955929658" Tag="78" IconVisible="True" LeftMargin="263.0000" RightMargin="873.0000" TopMargin="14.0000" BottomMargin="56.0000" InnerActionSpeed="1.0000" ctype="ProjectNodeObjectData">
                <Size />
                <AnchorPoint />
                <Position X="263.0000" Y="56.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.2315" Y="0.8000" />
                <PreSize />
                <FileData Type="Normal" Path="ui/panel_resource.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="ProjectNode_2" ActionTag="-2132418966" Tag="84" IconVisible="True" LeftMargin="493.0000" RightMargin="643.0000" TopMargin="14.0000" BottomMargin="56.0000" InnerActionSpeed="1.0000" ctype="ProjectNodeObjectData">
                <Size />
                <AnchorPoint />
                <Position X="493.0000" Y="56.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.4340" Y="0.8000" />
                <PreSize />
                <FileData Type="Normal" Path="ui/panel_resource.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="ProjectNode_3" ActionTag="1549136056" Tag="90" IconVisible="True" LeftMargin="723.0000" RightMargin="413.0000" TopMargin="14.0000" BottomMargin="56.0000" InnerActionSpeed="1.0000" ctype="ProjectNodeObjectData">
                <Size />
                <AnchorPoint />
                <Position X="723.0000" Y="56.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.6364" Y="0.8000" />
                <PreSize />
                <FileData Type="Normal" Path="ui/panel_resource.csd" Plist="" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
            <Position X="568.0000" Y="640.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="1.0000" />
            <PreSize X="1.0000" Y="0.1094" />
            <FileData Type="Normal" Path="images/ui/ui_130.png" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="Sprite_1" ActionTag="638629582" Tag="65" IconVisible="False" LeftMargin="568.0000" RightMargin="378.0000" TopMargin="81.0000" BottomMargin="525.0000" FlipX="True" ctype="SpriteObjectData">
            <Size X="190.0000" Y="34.0000" />
            <Children>
              <AbstractNodeData Name="Sprite_1_0" ActionTag="1944274651" Tag="66" IconVisible="False" LeftMargin="-190.0000" RightMargin="190.0000" ctype="SpriteObjectData">
                <Size X="190.0000" Y="34.0000" />
                <AnchorPoint ScaleX="1.0000" />
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize />
                <FileData Type="Normal" Path="images/ui/ui_134.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="lbl_level" ActionTag="-1486534749" Tag="118" IconVisible="False" LeftMargin="-100.0000" RightMargin="190.0000" TopMargin="2.0000" BottomMargin="2.0000" IsCustomSize="True" FontSize="20" LabelText="LV:{0}" VerticalAlignmentType="VT_Center" OutlineSize="1" ShadowOffsetX="2" ShadowOffsetY="-2" ctype="TextObjectData">
                <Size X="100.0000" Y="30.0000" />
                <AnchorPoint ScaleY="0.5000" />
                <Position X="-100.0000" Y="17.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="-0.5263" Y="0.5000" />
                <PreSize X="0.5263" Y="0.8824" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="lbl_score" ActionTag="-23083633" Tag="119" IconVisible="False" LeftMargin="10.0000" RightMargin="30.0000" TopMargin="2.0000" BottomMargin="2.0000" IsCustomSize="True" FontSize="20" LabelText="战力:{0}" VerticalAlignmentType="VT_Center" OutlineSize="1" ShadowOffsetX="2" ShadowOffsetY="-2" ctype="TextObjectData">
                <Size X="150.0000" Y="30.0000" />
                <AnchorPoint ScaleY="0.5000" />
                <Position X="10.0000" Y="17.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.0526" Y="0.5000" />
                <PreSize X="0.7895" Y="0.8824" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleY="0.5000" />
            <Position X="568.0000" Y="542.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.8469" />
            <PreSize />
            <FileData Type="Normal" Path="images/ui/ui_134.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="gift_node" ActionTag="1672601470" Tag="613" IconVisible="True" LeftMargin="1104.0273" RightMargin="31.9727" TopMargin="93.5120" BottomMargin="546.4880" InnerActionSpeed="1.0000" ctype="ProjectNodeObjectData">
            <Size />
            <AnchorPoint />
            <Position X="1104.0273" Y="546.4880" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.9719" Y="0.8539" />
            <PreSize />
            <FileData Type="Normal" Path="ui/gift_panel.csd" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="rotate_label_panel" ActionTag="-1577118174" Tag="486" IconVisible="False" LeftMargin="120.6489" RightMargin="615.3511" TopMargin="579.7649" BottomMargin="25.2351" TouchEnable="True" BackColorAlpha="102" ColorAngle="90.0000" ctype="PanelObjectData">
            <Size X="400.0000" Y="35.0000" />
            <Children>
              <AbstractNodeData Name="lbl_rotate" ActionTag="1842598212" Tag="219" IconVisible="False" LeftMargin="5.0000" RightMargin="15.0000" IsCustomSize="True" FontSize="26" LabelText="这里是聊天滚动文字" VerticalAlignmentType="VT_Center" OutlineSize="1" ShadowOffsetX="2" ShadowOffsetY="-2" ctype="TextObjectData">
                <Size X="380.0000" Y="35.0000" />
                <AnchorPoint />
                <Position X="5.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.0125" />
                <PreSize X="0.9500" Y="1.0000" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position X="120.6489" Y="25.2351" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.1062" Y="0.0394" />
            <PreSize X="0.3521" Y="0.0547" />
            <SingleColor A="255" R="150" G="200" B="255" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="btn_redemption" ActionTag="-137447068" Tag="58" IconVisible="False" LeftMargin="30.5000" RightMargin="986.5000" TopMargin="91.5000" BottomMargin="491.5000" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="89" Scale9Height="35" OutlineSize="1" ShadowOffsetX="2" ShadowOffsetY="-2" ctype="ButtonObjectData">
            <Size X="119.0000" Y="57.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="90.0000" Y="520.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0792" Y="0.8125" />
            <PreSize X="0.1048" Y="0.0891" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Normal" Path="images/button/button_85.png" Plist="" />
            <PressedFileData Type="Normal" Path="images/button/button_85.png" Plist="" />
            <NormalFileData Type="Normal" Path="images/button/button_84.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>