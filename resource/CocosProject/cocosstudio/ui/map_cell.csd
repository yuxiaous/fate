<GameProjectFile>
  <PropertyGroup Type="Layer" Name="map_cell" ID="1d9b2303-e81d-4a7d-b30a-a92fe0571759" Version="2.2.9.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="60" Speed="1.0000" ActivedAnimationName="indicator">
        <Timeline ActionTag="-1516836392" Property="Position">
          <PointFrame FrameIndex="0" X="100.0000" Y="335.0000">
            <EasingData Type="2" />
          </PointFrame>
          <PointFrame FrameIndex="30" X="100.0000" Y="370.0000">
            <EasingData Type="1" />
          </PointFrame>
          <PointFrame FrameIndex="60" X="100.0000" Y="335.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="indicator" StartIndex="0" EndIndex="60">
          <RenderColor A="255" R="107" G="142" B="35" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="root" Tag="828" ctype="GameLayerObjectData">
        <Size X="200.0000" Y="450.0000" />
        <Children>
          <AbstractNodeData Name="img_sel" ActionTag="559193641" Tag="897" IconVisible="False" LeftMargin="10.5000" RightMargin="10.5000" TopMargin="133.0000" BottomMargin="5.0000" Scale9Enable="True" LeftEage="32" RightEage="32" TopEage="32" BottomEage="32" Scale9OriginX="32" Scale9OriginY="32" Scale9Width="2" Scale9Height="2" ctype="ImageViewObjectData">
            <Size X="179.0000" Y="312.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="100.0000" Y="161.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.3578" />
            <PreSize X="0.8950" Y="0.6933" />
            <FileData Type="Normal" Path="images/ui/ui_155.png" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="btn_touch" ActionTag="2104285716" Tag="999" IconVisible="False" LeftMargin="15.0000" RightMargin="15.0000" TopMargin="138.0000" BottomMargin="10.0000" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="140" Scale9Height="280" OutlineSize="1" ShadowOffsetX="2" ShadowOffsetY="-2" ctype="ButtonObjectData">
            <Size X="170.0000" Y="302.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="100.0000" Y="161.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.3578" />
            <PreSize X="0.8500" Y="0.6711" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Normal" Path="images/ui/ui_154.png" Plist="" />
            <PressedFileData Type="Normal" Path="images/ui/ui_154.png" Plist="" />
            <NormalFileData Type="Normal" Path="images/ui/ui_154.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="sp_icon" ActionTag="2108052926" Tag="896" IconVisible="False" LeftMargin="29.0000" RightMargin="29.0000" TopMargin="197.0000" BottomMargin="117.0000" ctype="SpriteObjectData">
            <Size X="142.0000" Y="136.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="100.0000" Y="185.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.4111" />
            <PreSize />
            <FileData Type="Normal" Path="images/icon/map/map_0.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="sp_drop_1" ActionTag="2115433956" Tag="16" IconVisible="False" LeftMargin="110.0000" RightMargin="4.0000" TopMargin="272.0000" BottomMargin="92.0000" ctype="SpriteObjectData">
            <Size X="86.0000" Y="86.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="153.0000" Y="135.0000" />
            <Scale ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.7650" Y="0.3000" />
            <PreSize />
            <FileData Type="Normal" Path="images/icon/item/701.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="sp_drop_2" ActionTag="-472428759" Tag="17" IconVisible="False" LeftMargin="75.0000" RightMargin="39.0000" TopMargin="272.0000" BottomMargin="92.0000" ctype="SpriteObjectData">
            <Size X="86.0000" Y="86.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="118.0000" Y="135.0000" />
            <Scale ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5900" Y="0.3000" />
            <PreSize />
            <FileData Type="Normal" Path="images/icon/item/701.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="sp_drop_3" ActionTag="572724319" Tag="18" IconVisible="False" LeftMargin="40.0000" RightMargin="74.0000" TopMargin="272.0000" BottomMargin="92.0000" ctype="SpriteObjectData">
            <Size X="86.0000" Y="86.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="83.0000" Y="135.0000" />
            <Scale ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.4150" Y="0.3000" />
            <PreSize />
            <FileData Type="Normal" Path="images/icon/item/701.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="lbl_name" ActionTag="-1826131819" Tag="898" IconVisible="False" LeftMargin="32.0000" RightMargin="32.0000" TopMargin="162.0000" BottomMargin="262.0000" IsCustomSize="True" FontSize="22" LabelText="地图名称" HorizontalAlignmentType="HT_Center" VerticalAlignmentType="VT_Center" OutlineSize="1" ShadowOffsetX="2" ShadowOffsetY="-2" ctype="TextObjectData">
            <Size X="136.0000" Y="26.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="100.0000" Y="275.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.6111" />
            <PreSize X="0.6800" Y="0.0578" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="lbl_level" ActionTag="-950323992" Tag="899" IconVisible="False" LeftMargin="45.0000" RightMargin="55.0000" TopMargin="347.0000" BottomMargin="77.0000" IsCustomSize="True" FontSize="20" LabelText="LV:{0}" VerticalAlignmentType="VT_Center" OutlineSize="1" ShadowOffsetX="2" ShadowOffsetY="-2" ctype="TextObjectData">
            <Size X="100.0000" Y="26.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="95.0000" Y="90.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.4750" Y="0.2000" />
            <PreSize X="0.5000" Y="0.0578" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="lbl_score" ActionTag="2016075274" Tag="900" IconVisible="False" LeftMargin="45.0000" RightMargin="55.0000" TopMargin="385.3205" BottomMargin="38.6795" IsCustomSize="True" FontSize="20" LabelText="战力:{0}" VerticalAlignmentType="VT_Center" OutlineSize="1" ShadowOffsetX="2" ShadowOffsetY="-2" ctype="TextObjectData">
            <Size X="100.0000" Y="26.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="95.0000" Y="51.6795" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.4750" Y="0.1148" />
            <PreSize X="0.5000" Y="0.0578" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="sp_indicator" ActionTag="-1516836392" Tag="916" IconVisible="False" LeftMargin="84.5000" RightMargin="84.5000" TopMargin="99.0000" BottomMargin="319.0000" ctype="SpriteObjectData">
            <Size X="31.0000" Y="32.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="100.0000" Y="335.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.7444" />
            <PreSize />
            <FileData Type="Normal" Path="images/ui/ui_43.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>